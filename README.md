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

The AD2 recording has $`N = 4194304`$ samples taken at sampling ratio $`F = 10^4 `$ sps. One way to create multiple random streams is to split the input stream using **polyphase decomposition**. We define $`x(n)`$ as the input stream where $` n \in \{0, 1, \dots N-1\}`$. 
We then split $`x(n)`$ into K downsampled delayed streams defined as $`x_{i}(m) = x(K \cdot m + i) `$ where $` i \in \{0, 1, \dots K-1\}`$ is the stream index and $` m \in \{0, 1, \dots M -1 \}`$ and where $`M = \lfloor N/K \rfloor`$.
Correlation of two sequences of length $`M`$ is defined as
```math
\mathbf{R}_{x,y}(k) = \sum_{i=0}^{k} \tilde{x}(i-k) \tilde{y}(i) \quad \forall \quad k \in \langle 1-M, M-1\rangle, 
```
where $`\tilde{x}(n)`$ is sequence $`x(n)`$ appended with $`M-1`$ zero samples. In vector notation we may define $`\mathbf{\tilde{x}} \in \mathbb{R}^{2M-2 \times 1}`$ as $`2M-1 \times 1`$ vector containing entries of $`\tilde{x}(n)`$.
Correlation can be implemented more efficiently via FFT algorithm as
```math
\mathbf{R}_{x,y}(k) = ifft\Big\{ fft\big\{\mathbf{\tilde{x}} \big\} \odot fft \big\{ \mathbf{\tilde{y}} \big\}  \Big\} \quad \forall \quad k \in \langle 1-M, M-1\rangle,
```
The following figures illustrate the correlation function output for $`\mathbf{R}_{x_0, x_0}(k)`$ (left) and $`\mathbf{R}_{x_0, x_1}(k)`$ (right).
| $`\mathbf{R}_{x_0, x_0}(k)`$  |   $`\mathbf{R}_{x_0, x_1}(k)`$   |
|:-------------------------:|:-------------------------:|
| <img src="/images/R_ii_1.jpg" width="400"  title="autocorrelation"> | <img src="/images/R_ij_1.jpg" width="400"  title="covariance">  |

Based on the correlation function we may define the covariance matrix as 
```math
\mathbf{C} = 
\begin{pmatrix}
max \big\{ \mathbf{R}_{x_0, x_0}(k)\big\} & max \big\{ \mathbf{R}_{x_0, x_1}(k)\big\} & \dots & max \big\{ \mathbf{R}_{x_0, x_{K-1}}(k)\big\}\\
max \big\{ \mathbf{R}_{x_1, x_0}(k)\big\} & max \big\{ \mathbf{R}_{x_1, x_1}(k)\big\} & \dots & max \big\{ \mathbf{R}_{x_1, x_{K-1}}(k)\big\}\\
\vdots & \vdots & \ddots & \vdots \\
max \big\{ \mathbf{R}_{x_{K-1}, x_0}(k)\big\} & max \big\{ \mathbf{R}_{x_{K-1}, x_1}(k)\big\} & \dots & max \big\{ \mathbf{R}_{x_{K-1}, x_{K-1}}(k)\big\}
\end{pmatrix},
```
and for our measurement it yields (with lower triangular part left out)
<p align="center">
  <img src="/images/CovMat_1.JPG" width="800"  title="covariance matrix" align ="center">
</p>

Even with sampling rate as low as $`F = 10^4`$ sps our samples are still quite highly correlated. Best independence is achieved for delays close to  $`K/2`$ (green section of the covariance matrix). 

## Digital Output Measurements 

Analog output of the TRN generator is also sampled by Arduino Nano (at much lower sampling rate than with Analog Discovery 2).  



Link test [Google][2], [Yahoo!][3].


  [1]: https://github.com/nschloe/xhub
  [2]: https://www.google.com/
  [3]: https://www.yahoo.com/


<!---

OTHER LINKS:

How-to link google drive images to Github markdown files:
https://stackoverflow.com/questions/55803682/add-google-drive-images-to-readme-md-on-github

Markdown tutorial:
https://www.w3schools.io/file/markdown-images/

xhub - google chrome extension for typing LaTeX equations directly into markdown files:
https://github.com/nschloe/xhub

--->
