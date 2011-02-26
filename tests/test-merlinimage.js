var merlin = require('../merlin'),
    assert = require('assert'),
    util = require('util'),
    fs = require('fs'); 

function getImageInfo(m, cb) {
    cb(m.info());
}

module.exports = {
    'test image info': function() {
        fs.readFile(__dirname + '/source/merlin.png', function(err, buffer) {
            var m = new merlin.MerlinImage(buffer);

            getImageInfo(m, function(info) {
                assert.equal(info.height, 400);
                assert.equal(info.width, 640);
                assert.equal(info.size, 10025);
                assert.equal(info.resolution.x, 28.35);
                assert.equal(info.resolution.y, 28.35);
            });
        });
    },
    'test resize 200x200': function() {
        fs.readFile(__dirname + '/source/merlin.png', function(err, buffer) {
            var m = new merlin.MerlinImage(buffer);
            var new_m = m.resize(200, 200);

            getImageInfo(new_m, function(size) {
                assert.equal(size.height, 200);
                assert.equal(size.width, 200);
            });
        });
    },
    'test scale 200x200': function() {
        fs.readFile(__dirname + '/source/merlin.png', function(err, buffer) {
            var m = new merlin.MerlinImage(buffer);
            var new_m = m.scale(200, 200);
            getImageInfo(new_m, function(size) {
                assert.equal(size.height, 200);
                assert.equal(size.width, 200);
            });
        });
    }
}
