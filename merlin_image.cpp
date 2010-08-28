#include "merlin_image.h":

namespace merlin {

Handle<Value> MerlinImage::New(const Arguments& args) {
    HandleScope scope;
    MerlinImage* img = new MerlinImage();
    img->Wrap(args.This());
    return args.This();
  }

MerlinImage::MerlinImage() {

}

}
