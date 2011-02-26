#include <string.h>
#include "merlin_image.h"
#include "buffer_compat.h"

namespace merlin {

    Persistent<FunctionTemplate> MerlinImage::constructor_template;

    Handle<Value> MerlinImage::New(const Arguments& args) {
        HandleScope scope;
        
        size_t len = BufferLength(args[0]->ToObject());
        node::Buffer *tmp = node::Buffer::New(len);
        memcpy(BufferData(tmp), BufferData(args[0]->ToObject()), len);
        MerlinImage* img = new MerlinImage(tmp);
        img->Wrap(args.This());
        return scope.Close(args.This());
    }

    Handle<Value> MerlinImage::GetBuffer(const Arguments& args) {
        HandleScope scope;

        MerlinImage *img = ObjectWrap::Unwrap<MerlinImage>(args.This());
        Handle<Value> buf = img->buffer->handle_;

        return scope.Close(buf);
    }

    MagickWand* MerlinImage::ReadImage(MerlinImage *img){
        MagickWand* wand = NewMagickWand();
        MagickReadImageBlob(wand, reinterpret_cast<unsigned char*>(BufferData(img->buffer)), BufferLength(img->buffer));
        return wand;
    }

    Handle<Value> MerlinImage::WriteImage(MagickWand *wand){
        size_t length;
        unsigned char* data = MagickWriteImageBlob(wand, &length);
        node::Buffer *buf = node::Buffer::New(length);
        char *buff_data = BufferData(buf);
        memcpy(buff_data, data, length);
        MagickRelinquishMemory(data);
        DestroyMagickWand(wand);

        v8::Handle<v8::Value> argv[1] = {buf->handle_};
        return MerlinImage::constructor_template->GetFunction()->NewInstance(1, argv);
    }

    Handle<Value> MerlinImage::AddImage(const Arguments& args) {
        HandleScope scope;
        MagickWand* wand = MerlinImage::ReadImage(  ObjectWrap::Unwrap<MerlinImage>(args.This()) );

        MerlinImage *mi = ObjectWrap::Unwrap<MerlinImage>(args[0]->ToObject());

        MagickAddImage(wand, MerlinImage::ReadImage(mi));

        return scope.Close(MerlinImage::WriteImage(wand));
    }

    /**
     *   Type are:
     *   - Uniform 0
     *   - Gaussian 1
     *   - Multiplicative 2
     *   - Impulse 3
     *   - Laplacian 4
     *   - Poisson 5
     */
    Handle<Value> MerlinImage::AddNoiseImage(const Arguments& args) {
        HandleScope scope;
        MagickWand* wand = MerlinImage::ReadImage(  ObjectWrap::Unwrap<MerlinImage>(args.This()) );

        const int type = args[0]->IntegerValue();
        NoiseType t;
        switch(type) {
            case 0:
                t = UniformNoise;
                break;
            case 1:
                t = GaussianNoise;
                break;
            case 2:
                t = MultiplicativeGaussianNoise;
                break;
            case 3:
                t = ImpulseNoise;
                break;
            case 4:
                t = LaplacianNoise;
                break;
            case 5:
                t = PoissonNoise;
                break;
        }

        MagickAddNoiseImage(wand, t);

        return scope.Close(MerlinImage::WriteImage(wand));
    }

    Handle<Value> MerlinImage::BlurImage(const Arguments& args) {
        HandleScope scope;
        MagickWand* wand = MerlinImage::ReadImage(  ObjectWrap::Unwrap<MerlinImage>(args.This()) );

        const double radius = args[0]->NumberValue();
        const double sigma = args[1]->NumberValue();
        MagickBlurImage(wand, radius, sigma);

        return scope.Close(MerlinImage::WriteImage(wand));
    }

    Handle<Value> MerlinImage::CharcoalImage(const Arguments& args) {
        HandleScope scope;
        MagickWand* wand = MerlinImage::ReadImage(  ObjectWrap::Unwrap<MerlinImage>(args.This()) );

        const double radius = args[0]->NumberValue();
        const double sigma = args[1]->NumberValue();
        MagickCharcoalImage(wand, radius, sigma);

        return scope.Close(MerlinImage::WriteImage(wand));
    }

    Handle<Value> MerlinImage::ChopImage(const Arguments& args) {
        HandleScope scope;
        MagickWand* wand = MerlinImage::ReadImage(  ObjectWrap::Unwrap<MerlinImage>(args.This()) );


        int width = args[0]->IntegerValue();
        int height = args[1]->IntegerValue();
        int x = args[2]->IntegerValue();
        int y = args[3]->IntegerValue();
        MagickChopImage(wand, width, height, x, y);

        return scope.Close(MerlinImage::WriteImage(wand));
    }

    Handle<Value> MerlinImage::ClipImage(const Arguments& args) {
        HandleScope scope;
        MagickWand* wand = MerlinImage::ReadImage(  ObjectWrap::Unwrap<MerlinImage>(args.This()) );

        MagickClipImage(wand);

        return scope.Close(MerlinImage::WriteImage(wand));
    }

    Handle<Value> MerlinImage::ClipPathImage(const Arguments& args) {
        HandleScope scope;
        MagickWand* wand = MerlinImage::ReadImage(  ObjectWrap::Unwrap<MerlinImage>(args.This()) );

        const String::Utf8Value pathname(args[0]);
        const unsigned int inside = args[1]->IntegerValue();
        MagickClipPathImage(wand, *pathname, inside);

        return scope.Close(MerlinImage::WriteImage(wand));
    }

    Handle<Value> MerlinImage::CoalesceImages(const Arguments& args) {
        HandleScope scope;
        MagickWand* wand = MerlinImage::ReadImage(  ObjectWrap::Unwrap<MerlinImage>(args.This()) );

        const int len = args.Length();
        for (int i = 0; i < len; i++) {
            MerlinImage *mi = ObjectWrap::Unwrap<MerlinImage>(args[i]->ToObject());
            MagickAddImage(wand, MerlinImage::ReadImage(mi));
        }

        MagickWand* mosaicWand = MagickCoalesceImages(wand);

        return scope.Close(MerlinImage::WriteImage(mosaicWand));
    }

    Handle<Value> MerlinImage::CommentImage(const Arguments& args) {
        HandleScope scope;
        MagickWand* wand = MerlinImage::ReadImage(  ObjectWrap::Unwrap<MerlinImage>(args.This()) );

        const String::Utf8Value pathname(args[0]);
        MagickCommentImage(wand, *pathname);

        return scope.Close(MerlinImage::WriteImage(wand));
    }

    Handle<Value> MerlinImage::CropImage(const Arguments& args) {
        HandleScope scope;
        MagickWand* wand = MerlinImage::ReadImage(  ObjectWrap::Unwrap<MerlinImage>(args.This()) );

        int width = args[0]->IntegerValue();
        int height = args[1]->IntegerValue();
        int x = args[2]->IntegerValue();
        int y = args[3]->IntegerValue();
        MagickCropImage(wand, width, height, x, y);

        return scope.Close(MerlinImage::WriteImage(wand));
    }

    Handle<Value> MerlinImage::ImageInfo(const Arguments& args) {
        HandleScope scope;
        MagickWand* wand = MerlinImage::ReadImage(  ObjectWrap::Unwrap<MerlinImage>(args.This()) );

        Local<Object> size = Object::New();
        size->Set(String::NewSymbol("width"), Number::New(MagickGetImageWidth(wand)));
        size->Set(String::NewSymbol("height"), Number::New(MagickGetImageHeight(wand)));

        return scope.Close(size);
    }

    Handle<Value> MerlinImage::MosaicImages(const Arguments& args) {
        HandleScope scope;
        MagickWand* wand = MerlinImage::ReadImage(  ObjectWrap::Unwrap<MerlinImage>(args.This()) );

        const int len = args.Length();
        for (int i = 0; i < len; i++) {
            MerlinImage *mi = ObjectWrap::Unwrap<MerlinImage>(args[i]->ToObject());
            MagickAddImage(wand, MerlinImage::ReadImage(mi));
        }

        MagickWand* mosaicWand = MagickMosaicImages(wand);

        return scope.Close(MerlinImage::WriteImage(mosaicWand));
    }

    Handle<Value> MerlinImage::NegateImage(const Arguments& args) {
        HandleScope scope;
        MagickWand* wand = MerlinImage::ReadImage(  ObjectWrap::Unwrap<MerlinImage>(args.This()) );

        MagickNegateImage(wand, MagickFalse);

        return scope.Close(MerlinImage::WriteImage(wand));
    }

    Handle<Value> MerlinImage::ResizeImage(const Arguments& args) {
        HandleScope scope;
        MagickWand* wand = MerlinImage::ReadImage(  ObjectWrap::Unwrap<MerlinImage>(args.This()) );

        int width = args[0]->IntegerValue();
        int height = args[1]->IntegerValue();
        MagickResizeImage(wand, width, height, LanczosFilter, 1.0);

        return scope.Close(MerlinImage::WriteImage(wand));
    }

    Handle<Value> MerlinImage::RotateImage(const Arguments& args) {
        HandleScope scope;
        MagickWand* wand = MerlinImage::ReadImage(  ObjectWrap::Unwrap<MerlinImage>(args.This()) );

        double degrees = args[0]->NumberValue();
        PixelWand* pixelwand = NewPixelWand();
        MagickRotateImage(wand, pixelwand, degrees);
        DestroyPixelWand(pixelwand);

        return scope.Close(MerlinImage::WriteImage(wand));
    }

    Handle<Value> MerlinImage::ScaleImage(const Arguments& args) {
        HandleScope scope;
        MagickWand* wand = MerlinImage::ReadImage(  ObjectWrap::Unwrap<MerlinImage>(args.This()) );

        int width = args[0]->IntegerValue();
        int height = args[1]->IntegerValue();
        MagickScaleImage(wand, width, height);

        return scope.Close(MerlinImage::WriteImage(wand));
    }

    void MerlinImage::Initialize(Handle<Object> target) {
        HandleScope scope;

        Handle<FunctionTemplate> f = FunctionTemplate::New(MerlinImage::New);
        constructor_template = Persistent<FunctionTemplate>::New(f);
        constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
        constructor_template->SetClassName(String::NewSymbol("MerlinImage"));

        NODE_SET_PROTOTYPE_METHOD(constructor_template, "add",    MerlinImage::AddImage);
        NODE_SET_PROTOTYPE_METHOD(constructor_template, "addNoise",    MerlinImage::AddNoiseImage);
        NODE_SET_PROTOTYPE_METHOD(constructor_template, "blur",    MerlinImage::BlurImage);
        NODE_SET_PROTOTYPE_METHOD(constructor_template, "charcoal",    MerlinImage::CharcoalImage);
        NODE_SET_PROTOTYPE_METHOD(constructor_template, "chop",    MerlinImage::ChopImage);
        NODE_SET_PROTOTYPE_METHOD(constructor_template, "clip",    MerlinImage::ClipImage);
        NODE_SET_PROTOTYPE_METHOD(constructor_template, "clipPath",    MerlinImage::ClipPathImage);
        NODE_SET_PROTOTYPE_METHOD(constructor_template, "coalesce",  MerlinImage::CoalesceImages);
        NODE_SET_PROTOTYPE_METHOD(constructor_template, "comment",  MerlinImage::CommentImage);
        NODE_SET_PROTOTYPE_METHOD(constructor_template, "crop",      MerlinImage::CropImage);
        NODE_SET_PROTOTYPE_METHOD(constructor_template, "info",      MerlinImage::ImageInfo);
        NODE_SET_PROTOTYPE_METHOD(constructor_template, "mosaic",  MerlinImage::MosaicImages);
        NODE_SET_PROTOTYPE_METHOD(constructor_template, "negative",  MerlinImage::NegateImage);
        NODE_SET_PROTOTYPE_METHOD(constructor_template, "resize",    MerlinImage::ResizeImage);
        NODE_SET_PROTOTYPE_METHOD(constructor_template, "rotate",    MerlinImage::RotateImage);
        NODE_SET_PROTOTYPE_METHOD(constructor_template, "scale",    MerlinImage::ScaleImage);
        NODE_SET_PROTOTYPE_METHOD(constructor_template, "getBuffer", MerlinImage::GetBuffer);

        target->Set(String::NewSymbol("MerlinImage"), constructor_template->GetFunction());
    }

    MerlinImage::MerlinImage(node::Buffer *buffer) : buffer(buffer)
    {
    }

    MerlinImage::~MerlinImage() {
        delete buffer;
    }

}
