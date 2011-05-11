# Merlin - ImageMagick bindings for node.js #

## Usage ##

    var merlin = require('merlin');
    // create a new MerlinImage with a node Buffer containing data from an image
    var image = new merlin.MerlinImage(buffer);
    var new_image = image.resize(300, 400);
    // operations can be chained
    var new_image = new_image.negative().crop(100, 100, 0, 0);
    // when finished, get the buffer from the image
    res.write(new_image.getBuffer());

## Supported Operations ##
    MerlinImage.blur(/*double*/ radius, /*double*/ sigma)
    MerlinImage.charcoal(/*double*/ radius, /*double*/ sigma)
    MerlinImage.chop(/*int*/ width, /*int*/ height, /*int*/ xoffset, /*int*/ yoffset)
    MerlinImage.clip()
    MerlinImage.clipPath(/*String*/ pathname, /*int*/ inside)
    MerlinImage.crop(/*int*/ width, /*int*/ height, /*int*/ xoffset, /*int*/ yoffset)
    MerlinImage.mosaic(/*MerlinImage*/ image0[,/*MerlinImage*/ image1.../*MerlinImage*/ imageN])
    MerlinImage.negative()
    MerlinImage.resize(/*int*/ width, /*int*/ height)
    MerlinImage.rotate(/*double*/ degrees)


## More to come! ##


Trademarks?
============

Node.js™ is an official trademark of Joyent. This module is not formally related to or endorsed by the official Joyent Node.js open source or commercial project