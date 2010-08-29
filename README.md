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
    MerlinImage.rotate(/*double*/ degrees)
    MerlinImage.crop(/*int*/ width, /*int*/ height, /*int*/xoffset, /*int*/yoffset)
    MerlinImage.resize(/*int*/ width, /*int*/ height)
    MerlinImage.negative()

More to come!  We plan to create bindings for as much of the ImageMagick API as we can.

