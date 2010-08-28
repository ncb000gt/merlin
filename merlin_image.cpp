#include "merlin_image.h":

namespace merlin {

Handle<Value>
MerlinImage::New(const Arguments& args) {
    HandleScope scope;
    MerlinImage* img = new MerlinImage(ObjectWrap::Unwrap<node::Buffer>(args[0]->ToObject()));
    img->Wrap(args.This());
    return args.This();
  }

void
MerlinImage::Initialize(Handle<Object> target) {
    HandleScope scope;
    
    Handle<FunctionTemplate> f = FunctionTemplate::New(MerlinImage::New);
    constructor_template = Persistent<FunctionTemplate>::New(f);
    constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
    constructor_template->SetClassName(String::NewSymbol("MerlinImage"));

    target->Set(String::NewSymbol("MerlinImage"), constructor_template->GetFunction());
}

    MerlinImage::MerlinImage(node::Buffer *buffer) : 
    buffer(buffer)
    {
        wand = NewMagickWand();
    }

MerlinImage::~MerlinImage() {
    delete buffer;
    wand = DestroyMagickWand(wand);
}

}
