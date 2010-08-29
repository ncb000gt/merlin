#include <string.h>
#include "merlin_image.h":

namespace merlin {

Persistent<FunctionTemplate> MerlinImage::constructor_template;

Handle<Value>
MerlinImage::New(const Arguments& args) {
    HandleScope scope;
    node::Buffer *buf = ObjectWrap::Unwrap<node::Buffer>(args[0]->ToObject());
    MerlinImage* img = new MerlinImage(buf);
    img->Wrap(args.This());
    return scope.Close(args.This());
}

Handle<Value>
MerlinImage::GetBuffer(const Arguments& args) {
    HandleScope scope;

    MerlinImage *img = ObjectWrap::Unwrap<MerlinImage>(args.This());
    Handle<Value> buf = img->buffer->handle_;

    return scope.Close(buf);
}

Handle<Value> 
MerlinImage::CropImage(const Arguments& args) {
    HandleScope scope;

    MerlinImage *img = ObjectWrap::Unwrap<MerlinImage>(args.This());

    MagickReadImageBlob(img->wand, img->buffer->data(), img->buffer->length());
    MagickCropImage(img->wand, 10, 10, 10, 10);
    size_t length;
    unsigned char* data = MagickGetImageBlob(img->wand, &length);
    MagickSetFormat(img->wand, "JPEG");

    node::Buffer *buf = node::Buffer::New(length);

    char *buff_data = buf->data();
    strcpy(buff_data, (char *)data);

    return scope.Close(buf->handle_);
}

void
MerlinImage::Initialize(Handle<Object> target) {
    HandleScope scope;
    
    Handle<FunctionTemplate> f = FunctionTemplate::New(MerlinImage::New);
    constructor_template = Persistent<FunctionTemplate>::New(f);
    constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
    constructor_template->SetClassName(String::NewSymbol("MerlinImage"));

    NODE_SET_PROTOTYPE_METHOD(constructor_template, "cropImage", MerlinImage::CropImage);
    NODE_SET_PROTOTYPE_METHOD(constructor_template, "getBuffer", MerlinImage::GetBuffer);
    
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
