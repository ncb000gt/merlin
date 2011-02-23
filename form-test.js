//require.paths.unshift('/Users/polotek/src/merlin');
var http = require('http'),
    sys = require('sys'),
    formidable = require('formidable'),
      merlin = require('./merlin'),
    fs = require('fs');

var server = http.createServer(function(req, res){
    if(req.url == '/upload' && req.method.toLowerCase() == 'post'){
        res.writeHead(200, {'content-type': 'image/jpeg'});
        var form = new formidable.IncomingForm();
        form.onPart = function(part){
            var total = 0;
            var buffer = new Buffer(parseInt(req.headers['content-length']));
            part.on('data', function(data){
                data.copy(buffer, total, 0);
                total += data.length;
            });

	    //var buffer2 = fs.readFileSync(__dirname + '/test.jpg');

            part.on('end', function(){
                console.log('in: ', buffer.length);
		      //console.log('in2: ', buffer2.length);
                var m = new merlin.MerlinImage(buffer.slice(0, buffer.length));
		//var m2 = new merlin.MerlinImage(buffer2.slice(0, buffer2.length));
		//buffer = m.charcoal(10, 1).getBuffer();
                //buffer = m.chop(50, 50, 0, 0).getBuffer();
                //buffer = m.clip().getBuffer();
                //buffer = m.clipPath("test", 0).getBuffer();
		      //buffer = m.add(m2).resize(400,400).getBuffer();
		      //buffer = m.mosaic(m2).getBuffer();
                //buffer = m.crop(250, 250, 0, 0).getBuffer();
		      sys.debug('before resize');
		      /*m.resize(250, 250, function(image) {
					  sys.puts('resize cb');
					  image.getBuffer();
					  console.log('out: ', buffer.length);
					  res.write(buffer);
			       });*/
		      buffer = m.resize(250, 250).getBuffer();
		      sys.debug('after resize');
                //buffer = m.negative().crop(1000, 1000, 0, 0).resize(250, 250).getBuffer();
                //buffer = m.resize(250,250).rotate(-45.0).getBuffer();

		      // Noise and it's types
		      //buffer = m.addNoise(0).getBuffer();
		      //buffer = m.addNoise(1).getBuffer();
		      //buffer = m.addNoise(2).getBuffer();
		      //buffer = m.addNoise(3).getBuffer();
		      //buffer = m.addNoise(4).getBuffer();
		      //buffer = m.addNoise(5).getBuffer();

                console.log('out: ', buffer.length);
                res.write(buffer);
            });
        };

        form.parse(req, function(err, fields, files){
            res.end();
        });
        return;
    }

    res.writeHead(200, {'content-type': 'text/html'});
    res.end( '<form action="/upload" enctype="multipart/form-data" method="post">'
              + '<input type="file" name="upload" multiple="multiple"><br/>'
              + '<input type="submit" value="Upload">'
              + '</form>');

});

server.listen(8080);
