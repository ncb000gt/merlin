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

MagickWand*
MerlinImage::ReadImage(MerlinImage *img){
    MagickWand* wand = NewMagickWand();
    MagickReadImageBlob(wand, img->buffer->data(), img->buffer->length());
    return wand;
}

Handle<Value>
MerlinImage::WriteImage(MagickWand *wand){
    size_t length;
    unsigned char* data = MagickGetImageBlob(wand, &length);
    node::Buffer *buf = node::Buffer::New(length);
    char *buff_data = buf->data();
    memcpy(buff_data, data, length);
    wand = DestroyMagickWand(wand);

    v8::Handle<v8::Value> argv[1] = {buf->handle_};
    return MerlinImage::constructor_template->GetFunction()->NewInstance(1, argv);
}

Handle<Value> 
MerlinImage::CropImage(const Arguments& args) {
    HandleScope scope;
    MagickWand* wand = MerlinImage::ReadImage(  ObjectWrap::Unwrap<MerlinImage>(args.This()) );

    int width = args[0]->IntegerValue();
    int height = args[1]->IntegerValue();
    int x = args[2]->IntegerValue();
    int y = args[3]->IntegerValue();

    MagickCropImage(wand, width, height, x, y);
    return scope.Close(MerlinImage::WriteImage(wand));
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
}

MerlinImage::~MerlinImage() {
    delete buffer;
}

}
