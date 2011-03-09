#ifndef SRC_MERLIN_IMAGE_H_
#define SRC_MERLIN_IMAGE_H_

#include <cstdlib>
#include <node.h>
#include <node_buffer.h>
#include <wand/magick_wand.h>

#include "merlin.h"

using namespace v8;

namespace merlin {

class MerlinImage : public node::ObjectWrap {
  node::Buffer *buffer;

  public:
      static Persistent<FunctionTemplate> constructor_template;
      static void Initialize(Handle<Object>);
      static Handle<Value> New(const Arguments&);
      static Handle<Value> GetBuffer(const Arguments&);

      // image transformation functions
      static Handle<Value> AddImage(const Arguments&);
      static Handle<Value> AddNoiseImage(const Arguments&);
      static Handle<Value> BlurImage(const Arguments&);
      static Handle<Value> CharcoalImage(const Arguments&);
      static Handle<Value> ChopImage(const Arguments&);
      static Handle<Value> ClipImage(const Arguments&);
      static Handle<Value> ClipPathImage(const Arguments&);
      static Handle<Value> CoalesceImages(const Arguments&);
      static Handle<Value> CommentImage(const Arguments&);
      static Handle<Value> CropImage(const Arguments&);
      static Handle<Value> ImageHeight(const Arguments&);
      static Handle<Value> ImageInfo(const Arguments&);
      static Handle<Value> ImageResolution(const Arguments&);
      static Handle<Value> ImageSize(const Arguments&);
      static Handle<Value> ImageWidth(const Arguments&);
      static Handle<Value> MosaicImages(const Arguments&);      
      static Handle<Value> NegateImage(const Arguments&);
      static Handle<Value> ResizeImage(const Arguments&);
      static Handle<Value> RotateImage(const Arguments&);
      static Handle<Value> ScaleImage(const Arguments&);
      static Handle<Value> SharpenImage(const Arguments&);

      static MagickWand* ReadImage(MerlinImage*);
      static Handle<Value> WriteImage(MagickWand*);
      static node::Buffer* Buffer();

    explicit MerlinImage(node::Buffer *buffer);
    virtual ~MerlinImage();
};

} // namespace Merlin

#endif SRC_MERLIN_IMAGE_H_
