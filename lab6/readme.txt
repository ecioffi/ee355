Part1:

The quadratic regression generates lower residuals than the linear on the training dataset, but it seems to be overfitting based on the ridiculous negative result for predicting the price in the year 10000. This was verified based on examination of the x^2 coefficient -- it was near zero.

Part2:

Everything works as expected. I used a breast cancer dataset from UC Irvine -- http://archive.ics.uci.edu/ml/datasets/Breast+Cancer+Wisconsin+%28Diagnostic%29. Tumors were classified either as benign or malignant based on 30 parameters. Dataset information file from UCI included in part2 folder.