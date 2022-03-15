# TRN-Generator

## Info

In order to see the math formulas please download **xhub** chrome extension on
[xhub download link][1]

## Introduction
The first version of the True Random Number (TRN) generator based on amplified thermal noise is shown in figures below.
<!---
Display math:

```math
e^{i\pi} + 1 = 0
```

```math
\mathbf{A} = \begin{pmatrix}
1 & 1\\
0 & 1
\end{pmatrix}
```

and line math $`a^2 + b^2 = c^2`$.
--->



| Top view           |  Bottom view |
|:-------------------------:|:-------------------------:|
| <img src="/images/TRN_top_1_small.jpg" width="400"  title="top"> | <img src="/images/TRN_bottom_1_small.jpg" width="400"  title="bottom">  |




## Analog Output Measurements 

In order to properly analyze the TRN generator I performed measurements with [Digilent Analog Discovery 2](https://digilent.com/reference/test-and-measurement/analog-discovery-2/start). Resulting histogram / probability density function (PDF) and power spectral density (PSD) are calculated in MATLAB.


| PDF          |  PSD   |
|:-------------------------:|:-------------------------:|
| <img src="/images/PDF_2.jpg" width="400"  title="PDF"> | <img src="/images/PSD_2.jpg" width="400"  title="PSD">  |

Theoretical PDF formula is given by
```math
f_X(x) = \frac{1}{\sqrt{2 \pi} \sigma} e^{-\frac{(x-x_0)^2}{2 \sigma^2}}
```
where in our case variance equals $`\sigma^2 = 0.104 V^2`$ and DC offset $`x_0 = 0 V`$.


### Covariance Matrix

The AD2 recording has $`N = 4194304`$ samples taken at sampling ratio $`F = 10^4 `$ sps. One way to create multiple random streams is to split the input stream using **polyphase decomposition**. We define $`x(n)`$ as the input stream where $` n \in \{0, 1, \dots N-1\}`$. We then split it into K downsampled delayed streams defined as $`x_{i}(m) = x(K \cdot m + i) `$ where $` i \in \{0, 1, \dots K-1\}`$ is the stream index and $` m \in \{0, 1, \dots \lfloor N/K \rfloor-1\}`$.
Correlation of two sequences is defined as
```math
\mathbf{R}_{x,y}(k) = \sum_{i=0}^{k} \tilde{x}_{k-i} \tilde{y}_{i}, 
```
which is implemented more efficiently via FFT algorithm as
```math
\mathbf{R}_{x,y}(k) = \ifft\big\{ \mathbf{\tilde{X}} \odot \mathbf{\tilde{Y}}\big\}, 
```


## Digital Output Measurements 

Analog output of the TRN generator is also sampled by Arduino Nano (at much lower sampling rate than with Analog Discovery 2).  



Link test [Google][2], [Yahoo!][3].


  [1]: https://github.com/nschloe/xhub
  [2]: https://www.google.com/
  [3]: https://www.yahoo.com/


<!---
![image](https://drive.google.com/uc?export=view&id=13Kc26w20WehUby2Woa2oCrK1Yk4WDjpU)


Top view
<img src="https://drive.google.com/uc?export=view&id=13Vyqv_aGqLThN_RuAk9eDzAqz0dn7TaK" width=400 align=center title="TOP">
--->

<!---
Bottom view
<img src="https://drive.google.com/uc?export=view&id=13ThY_g2d9BxIqWg94jJebIAmiCJmlm3c" width=300 align=left>

<img src="https://drive.google.com/uc?export=view&id=13Vyqv_aGqLThN_RuAk9eDzAqz0dn7TaK" width=200 title="TOP">
<img src="https://drive.google.com/uc?export=view&id=13ThY_g2d9BxIqWg94jJebIAmiCJmlm3c" width=200 title="BOTTOM">

Spectrum magnitude
<img src="https://drive.google.com/uc?export=view&id=15Biexxwm-6txojOZyN4R7M9b6BPBS8EX" width=300 align=right  title="image Title">
--->


<!---

IMAGES:

Top
https://drive.google.com/file/d/13Vyqv_aGqLThN_RuAk9eDzAqz0dn7TaK/view?usp=sharing

Bottom
https://drive.google.com/file/d/13ThY_g2d9BxIqWg94jJebIAmiCJmlm3c/view?usp=sharing

Spectrum magnitude
https://drive.google.com/file/d/15Biexxwm-6txojOZyN4R7M9b6BPBS8EX/view?usp=sharing

probability density function - analog discovery 2 measurement, MATLAB postprocessing
https://drive.google.com/file/d/1FSJg3w4s5QrxNMIRrV_UNIXjQxbqoiCA/view?usp=sharing

Power Spectral Density - analog discovery 2 measurement, MATLAB postprocessing
https://drive.google.com/file/d/1Ed-3j3mNsdae_eKPQ9sJc3PuFAJO0Veo/view?usp=sharing

OTHER LINKS:

How-to link google drive images to Github markdown files:
https://stackoverflow.com/questions/55803682/add-google-drive-images-to-readme-md-on-github

Markdown tutorial:
https://www.w3schools.io/file/markdown-images/

xhub - google chrome extension for typing LaTeX equations directly into markdown files:
https://github.com/nschloe/xhub

--->
