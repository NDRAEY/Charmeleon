import png
import sys

if not sys.argv[1:]:
    print("NO arguments specified!!!")
    exit(1)

snippet = "int someimage_width = %d;\nint someimage_height = %d;\nchar someimage[%d] = {%s};"

image = png.Reader(sys.argv[-1])
(width,height,data,meta) = image.read_flat()
data = ','.join([str(d) for d in data])

print(snippet%(width,height,width*height*(3 if not meta['alpha'] else 4),data))
