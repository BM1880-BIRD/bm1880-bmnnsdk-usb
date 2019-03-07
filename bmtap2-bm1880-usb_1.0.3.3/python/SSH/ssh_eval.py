import os, sys
cur_dir = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(cur_dir, 'lib'))

from datasets.factory import get_imdb
import scipy.io as sio
import numpy as np

def boxoverlap(a, b):
    x1 = np.maximum(a[:, 0], b[0])
    y1 = np.maximum(a[:, 1], b[1])
    x2 = np.maximum(a[:, 2], b[2])
    y2 = np.maximum(a[:, 3], b[3])

    w = x2 - x1 + 1
    h = y2 - y1 + 1
    inter = w*h
    aarea = (a[:,2] - a[:,0] + 1) * (a[:,3] - a[:,1] + 1)
    barea = (b[2] - b[0] + 1) * (b[3] - b[1] + 1)
    o = inter / (aarea+barea-inter)
    o[w<=0] = 0
    o[h<=0] = 0

    return o

def image_evaluation(pred_info, gt_bbx, ignore, IoU_thresh):
    pred_recall = np.zeros(len(pred_info))
    recall_list = np.zeros(len(gt_bbx))
    proposal_list = np.ones(len(pred_info))

    pred_info[:,2] = pred_info[:,0] + pred_info[:,2]
    pred_info[:,3] = pred_info[:,1] + pred_info[:,3]
    gt_bbx[:,2] = gt_bbx[:,0] + gt_bbx[:,2]
    gt_bbx[:,3] = gt_bbx[:,1] + gt_bbx[:,3]
    for h in range(len(pred_info)):
        overlap_list = boxoverlap(gt_bbx, pred_info[h, 0:4])
        max_overlap = np.max(overlap_list)
        idx = np.argmax(overlap_list)
        if max_overlap >= IoU_thresh:
            if ignore[idx] == 0:
                recall_list[idx] = -1
                proposal_list[h] = -1
            elif recall_list[idx] == 0:
                recall_list[idx] = 1
        r_keep_index = np.argwhere(recall_list == 1)
        pred_recall[h] = len(r_keep_index)
    return pred_recall, proposal_list

def image_pr_info(thresh_num, pred_info, proposal_list, pred_recall):
    img_pr_info = np.zeros((thresh_num, 2))
    for t in xrange(thresh_num):
        thresh = 1-t/float(thresh_num)
        r_index = np.argwhere(pred_info[:, 4] >= thresh)
        if len(r_index) == 0:
            img_pr_info[t, 0] = 0
            img_pr_info[t, 1] = 0
        else:
            r_index = r_index[-1][0]
            p_index = np.argwhere(proposal_list[0:r_index+1] == 1)
            img_pr_info[t, 0] = len(p_index)
            img_pr_info[t, 1] = pred_recall[r_index]
    return img_pr_info

def dataset_pr_info(thresh_num, org_pr_curve, count_face):
    pr_curve = np.zeros((thresh_num, 2))
    for i in xrange(thresh_num):
        pr_curve[i, 0] = org_pr_curve[i, 1] / org_pr_curve[i, 0]
        pr_curve[i, 1] = org_pr_curve[i, 1] / count_face

    return pr_curve

def evaluation(norm_pred_list, gt_dat):
    IoU_thresh = 0.5
    event_num = 61
    thresh_num = 1000
    org_pr_curve = np.zeros((thresh_num, 2))
    count_face = 0

    for i in range(event_num):
        img_list = gt_dat['file_list'][i][0]
        gt_bbx_list = gt_dat['face_bbx_list'][i][0]
        pred_list = norm_pred_list[i]
        sub_gt_list = gt_dat['gt_list'][i][0]
        img_pr_info_list = []

        print("current event ", i)
        for j in xrange(len(img_list)):
            gt_bbx = gt_bbx_list[j][0]
            pred_info = pred_list[j]
            keep_index = sub_gt_list[j][0]
            count_face = count_face + len(keep_index)

            if len(gt_bbx) == 0 or len(pred_info) == 0:
                continue

            ignore = np.zeros(len(gt_bbx))
            if len(keep_index) != 0:
                ignore[keep_index-1] = 1

            pred_recall, proposal_list = image_evaluation(pred_info, gt_bbx, ignore, IoU_thresh)
            img_pr_info = image_pr_info(thresh_num, pred_info, proposal_list, pred_recall)
            img_pr_info_list.append(img_pr_info)

        org_pr_curve = org_pr_curve + np.sum(img_pr_info_list, axis=0)

    pr_curve = dataset_pr_info(thresh_num, org_pr_curve, count_face)
    return pr_curve

def norm_score(org_det_list):
    score_min = 1
    score_max = 0
    for event in org_det_list:
        for bbox in event:
            if len(bbox) != 0:
                score_list = bbox[:, 4]
                score_min = min(score_min, np.min(score_list))
                score_max = max(score_max, np.max(score_list))
    
    for event in org_det_list:
        for bbox in event:
            if len(bbox) != 0:
                score_list = bbox[:, 4]
                score_list = (score_list - score_min) / (score_max - score_min)
                bbox[:,4] = score_list

def main():
    gt_dat = sio.loadmat("lib/wider_eval_tools/ground_truth/wider_easy_val.mat")
    dets = []
    event_num = 61
    det_path = 'output/ssh/wider_val/SSH/detections'
    for event_idx in range(event_num):
        event_name = gt_dat['event_list'][event_idx][0][0]
        det = []
        for file_name in gt_dat['file_list'][event_idx][0]:
            fp = open(os.path.join(det_path, event_name, file_name[0][0]+'.txt'));
            fp.readline()
            if int(fp.readline()) > 0:
                cur_det = np.loadtxt(os.path.join(det_path, event_name, file_name[0][0]+'.txt'), skiprows=2)
                if len(cur_det.shape) > 1:
                    cur_det = cur_det[np.argsort(-cur_det[:,4])]
                    det.append(cur_det)
                else:
                    det.append(cur_det[np.newaxis, :])
            else:
                det.append([])
        dets.append(det)
    norm_score(dets)
    pr_curve = evaluation(dets, gt_dat)
    return pr_curve

if __name__ == '__main__':
  pr_curve = main()
