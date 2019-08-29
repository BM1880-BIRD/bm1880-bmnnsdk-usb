# This file was automatically generated by SWIG (http://www.swig.org).
# Version 3.0.8
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.





from sys import version_info
if version_info >= (2, 6, 0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_bmruntime', [dirname(__file__)])
        except ImportError:
            import _bmruntime
            return _bmruntime
        if fp is not None:
            try:
                _mod = imp.load_module('_bmruntime', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _bmruntime = swig_import_helper()
    del swig_import_helper
else:
    import _bmruntime
del version_info
try:
    _swig_property = property
except NameError:
    pass  # Python < 2.2 doesn't have 'property'.


def _swig_setattr_nondynamic(self, class_type, name, value, static=1):
    if (name == "thisown"):
        return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name, None)
    if method:
        return method(self, value)
    if (not static):
        if _newclass:
            object.__setattr__(self, name, value)
        else:
            self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)


def _swig_setattr(self, class_type, name, value):
    return _swig_setattr_nondynamic(self, class_type, name, value, 0)


def _swig_getattr_nondynamic(self, class_type, name, static=1):
    if (name == "thisown"):
        return self.this.own()
    method = class_type.__swig_getmethods__.get(name, None)
    if method:
        return method(self)
    if (not static):
        return object.__getattr__(self, name)
    else:
        raise AttributeError(name)

def _swig_getattr(self, class_type, name):
    return _swig_getattr_nondynamic(self, class_type, name, 0)


def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except Exception:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except AttributeError:
    class _object:
        pass
    _newclass = 0


class SwigPyIterator(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, SwigPyIterator, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, SwigPyIterator, name)

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _bmruntime.delete_SwigPyIterator
    __del__ = lambda self: None

    def value(self):
        return _bmruntime.SwigPyIterator_value(self)

    def incr(self, n=1):
        return _bmruntime.SwigPyIterator_incr(self, n)

    def decr(self, n=1):
        return _bmruntime.SwigPyIterator_decr(self, n)

    def distance(self, x):
        return _bmruntime.SwigPyIterator_distance(self, x)

    def equal(self, x):
        return _bmruntime.SwigPyIterator_equal(self, x)

    def copy(self):
        return _bmruntime.SwigPyIterator_copy(self)

    def next(self):
        return _bmruntime.SwigPyIterator_next(self)

    def __next__(self):
        return _bmruntime.SwigPyIterator___next__(self)

    def previous(self):
        return _bmruntime.SwigPyIterator_previous(self)

    def advance(self, n):
        return _bmruntime.SwigPyIterator_advance(self, n)

    def __eq__(self, x):
        return _bmruntime.SwigPyIterator___eq__(self, x)

    def __ne__(self, x):
        return _bmruntime.SwigPyIterator___ne__(self, x)

    def __iadd__(self, n):
        return _bmruntime.SwigPyIterator___iadd__(self, n)

    def __isub__(self, n):
        return _bmruntime.SwigPyIterator___isub__(self, n)

    def __add__(self, n):
        return _bmruntime.SwigPyIterator___add__(self, n)

    def __sub__(self, *args):
        return _bmruntime.SwigPyIterator___sub__(self, *args)
    def __iter__(self):
        return self
SwigPyIterator_swigregister = _bmruntime.SwigPyIterator_swigregister
SwigPyIterator_swigregister(SwigPyIterator)


_bmruntime.FMT_F32_swigconstant(_bmruntime)
FMT_F32 = _bmruntime.FMT_F32

_bmruntime.FMT_I8_swigconstant(_bmruntime)
FMT_I8 = _bmruntime.FMT_I8
class shape_t(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, shape_t, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, shape_t, name)
    __repr__ = _swig_repr
    __swig_setmethods__["dim"] = _bmruntime.shape_t_dim_set
    __swig_getmethods__["dim"] = _bmruntime.shape_t_dim_get
    if _newclass:
        dim = _swig_property(_bmruntime.shape_t_dim_get, _bmruntime.shape_t_dim_set)
    __swig_setmethods__["n"] = _bmruntime.shape_t_n_set
    __swig_getmethods__["n"] = _bmruntime.shape_t_n_get
    if _newclass:
        n = _swig_property(_bmruntime.shape_t_n_get, _bmruntime.shape_t_n_set)
    __swig_setmethods__["c"] = _bmruntime.shape_t_c_set
    __swig_getmethods__["c"] = _bmruntime.shape_t_c_get
    if _newclass:
        c = _swig_property(_bmruntime.shape_t_c_get, _bmruntime.shape_t_c_set)

    def __init__(self):
        this = _bmruntime.new_shape_t()
        try:
            self.this.append(this)
        except Exception:
            self.this = this
    __swig_destroy__ = _bmruntime.delete_shape_t
    __del__ = lambda self: None
shape_t_swigregister = _bmruntime.shape_t_swigregister
shape_t_swigregister(shape_t)


def shape_t4(n, c, h, w):
    return _bmruntime.shape_t4(n, c, h, w)
shape_t4 = _bmruntime.shape_t4
class Blob(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Blob, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Blob, name)
    __repr__ = _swig_repr

    def __init__(self, *args):
        this = _bmruntime.new_Blob(*args)
        try:
            self.this.append(this)
        except Exception:
            self.this = this
    __swig_destroy__ = _bmruntime.delete_Blob
    __del__ = lambda self: None

    def data(self):
        return _bmruntime.Blob_data(self)

    def shape(self):
        return _bmruntime.Blob_shape(self)

    def fmt(self):
        return _bmruntime.Blob_fmt(self)

    def count(self):
        return _bmruntime.Blob_count(self)

    def size(self):
        return _bmruntime.Blob_size(self)

    def dump(self):
        return _bmruntime.Blob_dump(self)
Blob_swigregister = _bmruntime.Blob_swigregister
Blob_swigregister(Blob)

class Net(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Net, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Net, name)
    __repr__ = _swig_repr

    def __init__(self, bmodel):
        this = _bmruntime.new_Net(bmodel)
        try:
            self.this.append(this)
        except Exception:
            self.this = this
    __swig_destroy__ = _bmruntime.delete_Net
    __del__ = lambda self: None

    def forward(self, input_blobs):
        return _bmruntime.Net_forward(self, input_blobs)

    def output(self, output_name):
        return _bmruntime.Net_output(self, output_name)
Net_swigregister = _bmruntime.Net_swigregister
Net_swigregister(Net)

class BlobVector(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, BlobVector, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, BlobVector, name)
    __repr__ = _swig_repr

    def iterator(self):
        return _bmruntime.BlobVector_iterator(self)
    def __iter__(self):
        return self.iterator()

    def __nonzero__(self):
        return _bmruntime.BlobVector___nonzero__(self)

    def __bool__(self):
        return _bmruntime.BlobVector___bool__(self)

    def __len__(self):
        return _bmruntime.BlobVector___len__(self)

    def __getslice__(self, i, j):
        return _bmruntime.BlobVector___getslice__(self, i, j)

    def __setslice__(self, *args):
        return _bmruntime.BlobVector___setslice__(self, *args)

    def __delslice__(self, i, j):
        return _bmruntime.BlobVector___delslice__(self, i, j)

    def __delitem__(self, *args):
        return _bmruntime.BlobVector___delitem__(self, *args)

    def __getitem__(self, *args):
        return _bmruntime.BlobVector___getitem__(self, *args)

    def __setitem__(self, *args):
        return _bmruntime.BlobVector___setitem__(self, *args)

    def pop(self):
        return _bmruntime.BlobVector_pop(self)

    def append(self, x):
        return _bmruntime.BlobVector_append(self, x)

    def empty(self):
        return _bmruntime.BlobVector_empty(self)

    def size(self):
        return _bmruntime.BlobVector_size(self)

    def swap(self, v):
        return _bmruntime.BlobVector_swap(self, v)

    def begin(self):
        return _bmruntime.BlobVector_begin(self)

    def end(self):
        return _bmruntime.BlobVector_end(self)

    def rbegin(self):
        return _bmruntime.BlobVector_rbegin(self)

    def rend(self):
        return _bmruntime.BlobVector_rend(self)

    def clear(self):
        return _bmruntime.BlobVector_clear(self)

    def get_allocator(self):
        return _bmruntime.BlobVector_get_allocator(self)

    def pop_back(self):
        return _bmruntime.BlobVector_pop_back(self)

    def erase(self, *args):
        return _bmruntime.BlobVector_erase(self, *args)

    def __init__(self, *args):
        this = _bmruntime.new_BlobVector(*args)
        try:
            self.this.append(this)
        except Exception:
            self.this = this

    def push_back(self, x):
        return _bmruntime.BlobVector_push_back(self, x)

    def front(self):
        return _bmruntime.BlobVector_front(self)

    def back(self):
        return _bmruntime.BlobVector_back(self)

    def assign(self, n, x):
        return _bmruntime.BlobVector_assign(self, n, x)

    def resize(self, *args):
        return _bmruntime.BlobVector_resize(self, *args)

    def insert(self, *args):
        return _bmruntime.BlobVector_insert(self, *args)

    def reserve(self, n):
        return _bmruntime.BlobVector_reserve(self, n)

    def capacity(self):
        return _bmruntime.BlobVector_capacity(self)
    __swig_destroy__ = _bmruntime.delete_BlobVector
    __del__ = lambda self: None
BlobVector_swigregister = _bmruntime.BlobVector_swigregister
BlobVector_swigregister(BlobVector)


def array2blob(data, shape):
    return _bmruntime.array2blob(data, shape)
array2blob = _bmruntime.array2blob

def blob2array(blob):
    return _bmruntime.blob2array(blob)
blob2array = _bmruntime.blob2array
# This file is compatible with both classic and new-style classes.

