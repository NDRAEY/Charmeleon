import png
import sys

if not sys.argv[1:]:
    print("NO arguments specified!!!")
    exit(1)

snippet = '''char* someimage_name = "Charmeleon image drawer by Andrey Pavlenko";
int someimage_width = %d;
int someimage_height = %d;
char someimage[%d] = {%s};'''

image = png.Reader(sys.argv[-1])
(width,height,data,meta) = image.read_flat()
data = ','.join([str(d) for d in data])

print(snippet%(width,height,width*height*(3 if not meta['alpha'] else 4),data))

sys.stderr.write(str(meta)+"\n")
