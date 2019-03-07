#ifndef TH_GENERIC_FILE
#define TH_GENERIC_FILE "generic/THStorage.h"
#else

#ifdef __cplusplus
#include <ATen/Allocator.h>
#include <ATen/StorageImpl.h>
#endif

/* on pourrait avoir un liste chainee
   qui initialise math, lab structures (or more).
   mouais -- complique.

   Pb: THMapStorage is kind of a class
   THLab_()... comment je m'en sors?

   en template, faudrait que je les instancie toutes!!! oh boy!
   Et comment je sais que c'est pour Cuda? Le type float est le meme dans les <>

   au bout du compte, ca serait sur des pointeurs float/double... etc... = facile.
   primitives??
 */

// Struct definition is moved to THStorage.hpp (so this file stays C compatible)

#ifdef __cplusplus
#define THStorage at::StorageImpl
#else
typedef struct at_Storage_Impl at_Storage_Impl;
#define THStorage at_Storage_Impl
#endif

// These used to be distinct types; for some measure of backwards compatibility and documentation
// alias these to the single THStorage type.
#define THFloatStorage THStorage
#define THDoubleStorage THStorage
#define THHalfStorage THStorage
#define THByteStorage THStorage
#define THCharStorage THStorage
#define THShortStorage THStorage
#define THIntStorage THStorage
#define THLongStorage THStorage

TH_API real* THStorage_(data)(const THStorage*);
TH_API ptrdiff_t THStorage_(size)(const THStorage*);
TH_API size_t THStorage_(elementSize)(void);

/* slow access -- checks everything */
TH_API void THStorage_(set)(THStorage*, ptrdiff_t, real);
TH_API real THStorage_(get)(const THStorage*, ptrdiff_t);

TH_API THStorage* THStorage_(new)(void);
TH_API THStorage* THStorage_(newWithSize)(ptrdiff_t size);
TH_API THStorage* THStorage_(newWithSize1)(real);
TH_API THStorage* THStorage_(newWithSize2)(real, real);
TH_API THStorage* THStorage_(newWithSize3)(real, real, real);
TH_API THStorage* THStorage_(newWithSize4)(real, real, real, real);
TH_API THStorage* THStorage_(newWithMapping)(const char *filename, ptrdiff_t size, int flags);

TH_API THStorage* THStorage_(newWithAllocator)(ptrdiff_t size,
                                               THAllocator* allocator);
#ifdef __cplusplus
TH_API THStorage* THStorage_(newWithDataAndAllocator)(
    at::DataPtr&& data, ptrdiff_t size, at::Allocator* allocator);
#endif

/* should not differ with API */
TH_API void THStorage_(setFlag)(THStorage *storage, const char flag);
TH_API void THStorage_(clearFlag)(THStorage *storage, const char flag);
TH_API void THStorage_(retain)(THStorage *storage);
TH_API void THStorage_(swap)(THStorage *storage1, THStorage *storage2);

/* might differ with other API (like CUDA) */
TH_API void THStorage_(free)(THStorage *storage);
TH_API void THStorage_(resize)(THStorage *storage, ptrdiff_t size);
TH_API void THStorage_(fill)(THStorage *storage, real value);

#endif
