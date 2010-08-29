#ifndef SRC_MERLIN_IMAGE_H_
#define SRC_MERLIN_IMAGE_H_

#include <cstdlib>
#include <node.h>
#include <node_buffer.h>
#include <wand/MagickWand.h>

#include "merlin.h"

using namespace v8;

namespace merlin {

class MerlinImage : public node::ObjectWrap {
  public:
      static Persistent<FunctionTemplate> constructor_template;
      static void Initialize(Handle<Object>);
      static Handle<Value> New(const Arguments&);
      static Handle<Value> GetBuffer(const Arguments&);

      // image transformation functions
      static Handle<Value> CropImage(const Arguments&);
      static Handle<Value> ResizeImage(const Arguments&);
      static Handle<Value> NegateImage(const Arguments&);
      static Handle<Value> RotateImage(const Arguments&);

      static MagickWand* ReadImage(MerlinImage*);
      static Handle<Value> WriteImage(MagickWand*);

    explicit MerlinImage(node::Buffer* buffer);
    virtual ~MerlinImage();

  private:
      node::Buffer *buffer;
};

} // namespace Merlin

#endif SRC_MERLIN_IMAGE_H_
