#ifndef YPIXMAP_H
#define YPIXMAP_H

#include <X11/X.h>
#include <X11/extensions/Xrender.h>
#include <X11/extensions/Xdamage.h>
#include "ref.h"
#include "upath.h"

class YImage;

class YPixmap: public virtual refcounted {
public:
    static ref<YPixmap> create(unsigned w, unsigned h, unsigned depth, bool mask = false);
    static ref<YPixmap> load(upath filename);
//    static ref<YPixmap> scale(ref<YPixmap> source, int width, int height);
    static ref<YPixmap> createFromImage(ref<YImage> image, unsigned depth);
    static ref<YPixmap> createFromPixmapAndMask(Pixmap pixmap,
                                                Pixmap mask,
                                                unsigned w, unsigned h);
    static ref<YPixmap> createFromPixmapAndMaskScaled(Pixmap pix, Pixmap mask,
                                                      unsigned width, unsigned height,
                                                      unsigned nw, unsigned nh);

    void replicate(bool horiz, bool copyMask);

    Pixmap pixmap() const { return fPixmap; }
    Pixmap mask() const { return fMask; }
    unsigned width() const { return fWidth; }
    unsigned height() const { return fHeight; }
    unsigned depth() const { return fDepth; }
    unsigned verticalOffset() const;
    ref<YImage> image();
    Pixmap pixmap32();
    Pixmap pixmap24();
    Pixmap pixmap(unsigned depth);
    Picture picture();
    void freePicture();
    ref<YPixmap> scale(unsigned w, unsigned h);
    ref<YPixmap> subimage(unsigned x, unsigned y, unsigned w, unsigned h);

private:
    YPixmap(Pixmap pixmap, Pixmap mask,
            unsigned width, unsigned height,
            unsigned depth, ref<YImage> image);
    virtual ~YPixmap();

    friend class YImage;

private:
    unsigned fWidth;
    unsigned fHeight;
    unsigned fDepth;

    Pixmap fPixmap;
    Pixmap fMask;
    Picture fPicture;
    ref<YImage> fImage;
    ref<YPixmap> fPixmap32;
    ref<YPixmap> fPixmap24;
};

#endif

// vim: set sw=4 ts=4 et:
