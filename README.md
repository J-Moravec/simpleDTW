# simpleDTW
This is naive implementation of Dynamic Time Warping algorithm, without any
optimization techniques. Still, it is around 40x faster than implementation
from `dtw` package.

Note that `dtw` package contains a little programing error, in file
`globalCostMatrix.R`, line 95, part of the `.Call` function call should be:
`PACKAGE="dtw"`. This function should thus look like:
```{R}
      out <- .Call("computeCM_Call",
                   wm,lm,cm,step.matrix, PACKAGE="dtw");
```

Otherwise R has problem with finding associated compiled library.

## How to install::
```{R}
    library("devtools")
    devtools::install_github("J-Moravec/simpleDTW")

```
