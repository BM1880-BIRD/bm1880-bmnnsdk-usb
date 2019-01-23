inst {
  name: "conv1_1_0_0_0"
  type: "bmnet_tl_load_stride_bmkernel"
  tl_layer_load_stride {
    stream_id: 0
    inst_id: 0
    depends_len: 0
    ga_src: 500
    la_dst: 1025
    Local_N: 2
    Local_C: 20
    Local_H: 1
    Local_W: 1
    Global_C: 20
    Global_H: 1
    Global_W: 1
    DoTranspose: false
    DoAligned: false
    isNeuron: false
  }
}

inst {
  type: "bmnet_tl_load_stride_bmkernel"
  tl_layer_load_stride {
    stream_id: 0
    inst_id: 0
    depends_len: 0
    ga_src: 0
    la_dst: 1000
    Local_N: 1
    Local_C: 20
    Local_H: 25
    Local_W: 1
    Global_C: 20
    Global_H: 25
    Global_W: 1
    DoTranspose: false
    DoAligned: false
    isNeuron: false
  }
}

inst {
  type: "bmnet_tl_load_stride_bmkernel"
  tl_layer_load_stride {
    stream_id: 0
    inst_id: 0
    depends_len: 0
    ga_src: 0
    la_dst: 1040
    Local_N: 1
    Local_C: 1
    Local_H: 28
    Local_W: 28
    Global_C: 1
    Global_H: 28
    Global_W: 28
    DoTranspose: false
    DoAligned: true
    isNeuron: true
  }
}

inst {
  type: "bmnet_tl_conv_forward_bmkernel"
  bm_tl_conv {
    stream_id: 0
    inst_id: 0
    depends_len: 0
    la_ifmap: 1040
    la_ofmap: 1824
    la_weight: 1000
    la_bias: 1025
    group_weight: 0
    group_bias: 0
    input_n: 1
    input_c: 1
    input_h: 28
    input_w: 28
    group: 1
    output_c: 20
    output_h: 24
    output_w: 24
    kh: 5
    kw: 5
    dh: 1
    dw: 1
    pad_h_top: 0
    pad_h_bottom: 0
    pad_w_left: 0
    pad_w_right: 0
    stride_h: 1
    stride_w: 1
    result_add: 0
    ctrl: 0
    rshift: 8
    do_bias: true
    use_winograd: false
    do_relu: false
    h_slice_skip_first: false
    h_slice_skip_last: false
  }
}

inst {
  type: "bmnet_tl_load_stride_bmkernel"
  tl_layer_load_stride {
    stream_id: 0
    inst_id: 0
    depends_len: 0
    ga_src: 540
    la_dst: 0
    Local_N: 1
    Local_C: 50
    Local_H: 25
    Local_W: 20
    Global_C: 50
    Global_H: 25
    Global_W: 20
    DoTranspose: false
    DoAligned: false
    isNeuron: false
  }
}

inst {
  name: "pool1_1_0_0_0"
  type: "bmnet_tl_pooling_forward_bmkernel"
  tl_pool {
    stream_id: 0
    inst_id: 0
    depends_len: 0
    ifmap_laddr: 1824
    ofmap_laddr: 1008
    input_n: 1
    input_c: 20
    input_h: 24
    input_w: 24
    output_n: 1
    output_c: 20
    output_h: 12
    output_w: 12
    kh: 2
    kw: 2
    stride_h: 2
    stride_w: 2
    pad_h_top: 0
    pad_h_bottom: 0
    pad_w_left: 0
    pad_w_right: 0
    is_avg_pooling: false
    right_shift_width: 8
    threshold_x_quantized: 160
  }
}

inst {
  type: "bmnet_tl_load_stride_bmkernel"
  tl_layer_load_stride {
    stream_id: 0
    inst_id: 0
    depends_len: 0
    ga_src: 25540
    la_dst: 1000
    Local_N: 2
    Local_C: 50
    Local_H: 1
    Local_W: 1
    Global_C: 50
    Global_H: 1
    Global_W: 1
    DoTranspose: false
    DoAligned: false
    isNeuron: false
  }
}

inst {
  name: "conv2_1_0_0_0"
  type: "bmnet_tl_conv_forward_bmkernel"
  bm_tl_conv {
    stream_id: 0
    inst_id: 0
    depends_len: 0
    la_ifmap: 1008
    la_ofmap: 1152
    la_weight: 0
    la_bias: 1000
    group_weight: 0
    group_bias: 0
    input_n: 1
    input_c: 20
    input_h: 12
    input_w: 12
    group: 1
    output_c: 50
    output_h: 8
    output_w: 8
    kh: 5
    kw: 5
    dh: 1
    dw: 1
    pad_h_top: 0
    pad_h_bottom: 0
    pad_w_left: 0
    pad_w_right: 0
    stride_h: 1
    stride_w: 1
    result_add: 0
    ctrl: 0
    rshift: 10
    do_bias: true
    use_winograd: false
    do_relu: false
    h_slice_skip_first: false
    h_slice_skip_last: false
  }
}

inst {
  name: "pool2_1_0_0_0"
  type: "bmnet_tl_pooling_forward_bmkernel"
  tl_pool {
    stream_id: 0
    inst_id: 0
    depends_len: 0
    ifmap_laddr: 1152
    ofmap_laddr: 0
    input_n: 1
    input_c: 50
    input_h: 8
    input_w: 8
    output_n: 1
    output_c: 50
    output_h: 4
    output_w: 4
    kh: 2
    kw: 2
    stride_h: 2
    stride_w: 2
    pad_h_top: 0
    pad_h_bottom: 0
    pad_w_left: 0
    pad_w_right: 0
    is_avg_pooling: false
    right_shift_width: 7
    threshold_x_quantized: 135
  }
}

inst {
  type: "bmnet_tl_store_stride_bmkernel"
  tl_layer_store_stride {
    stream_id: 0
    inst_id: 0
    depends_len: 0
    ga_dst: 784
    la_src: 0
    Local_N: 1
    Local_C: 50
    Local_H: 4
    Local_W: 4
    Global_C: 50
    Global_H: 4
    Global_W: 4
    DoTranspose: false
    DoAligned: true
    isNeuron: true
  }
}

inst {
  name: "ip1_1"
  type: "bmnet_fc_fixed_forward_bmkernel"
  fc {
    stream_id: 0
    inst_id: 0
    depends_len: 0
    bottom_data_gaddr: 784
    weight_data_gaddr: 25640
    bias_data_gaddr: 425640
    top_data_gaddr: 0
    input_row_num: 1
    input_col_num: 800
    weight_col_num: 500
    have_bias: 1
    do_activation: 0
    activation_method: 0
    activation_ga_slope: 1099511627775
    activation_channel_shared: 0
    activation_gt_scale: 0
    activation_gt_rshift: 0
    activation_le_scale: 0
    activation_le_rshift: 0
    weight_transpose: false
    left_shift_width: 3
    right_shift_width: 11
  }
}

inst {
  name: "ip2_1"
  type: "bmnet_fc_fixed_forward_bmkernel"
  fc {
    stream_id: 0
    inst_id: 0
    depends_len: 0
    bottom_data_gaddr: 500
    weight_data_gaddr: 426640
    bias_data_gaddr: 431640
    top_data_gaddr: 0
    input_row_num: 1
    input_col_num: 500
    weight_col_num: 10
    have_bias: 1
    do_activation: 0
    activation_method: 0
    activation_ga_slope: 1099511627775
    activation_channel_shared: 0
    activation_gt_scale: 0
    activation_gt_rshift: 0
    activation_le_scale: 0
    activation_le_rshift: 0
    weight_transpose: false
    left_shift_width: 3
    right_shift_width: 10
  }
}

