# How to use

## generator

```./generator [primitive] [options] [output]```

### primitive
* sphere
  - options: radius slices stacks
* cube
  - options: length divisions
* plane
  - options: length divisions
* cone
  - options: radius height slices stacks

### output
A .3d file to output. If path is not specified, the output is saved in same directory has executable.

## engine

```./engine [pathToConfig]```

### pathToConfig
A .xml file to load. If path is not specified, it assumes the file is in the same directory has executable.