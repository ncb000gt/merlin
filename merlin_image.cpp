#include "merlin_image.h":

namespace merlin {

Handle<Value> MerlinImage::New(const Arguments& args) {
    HandleScope scope;
    MerlinImage* img = new MerlinImage(ObjectWrap::Unwrap<node::Buffer>(args[0]->ToObject()));
    img->Wrap(args.This());
    return args.This();
  }

MerlinImage::MerlinImage(node::Buffer *buffer) : 
    buffer(buffer)
    {
        wand = NewMagickWand();
    }

MerlinImage::~MerlinImage() {
    wand = DestroyMagickWand(wand);
}

}
