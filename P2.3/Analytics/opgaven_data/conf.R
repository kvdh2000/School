conf <- function(n, d) 
{
  predicttest= predict (tree, newdata=testData)
  t=table(n, predicttest[,2] > d)
  
  TN=t[1]
  FP=t[2]
  FN=t[3]
  TP=t[4]
  
  sensitivity <- TP / (FN + TP)
  specificity <- TN / (TN + FP)
  accuracy <- (TN + TP) / (TN + TP + FP + FN)
  
  print(t)
  
  print(paste("Sensitivity = ", sensitivity))
  print(paste("Specificify = ", specificity))
  print(paste("Accuracy =    ", accuracy))
}

conf3 <- function(n, d) 
{
  predicttest= predict (tree, newdata=testData)
  t=table(n, predicttest[,2] > d)
  
  TN=t[1]
  FP=t[2]
  FN=t[3]
  TP=t[4]
  
  sensitivity <- TP / (FN + TP)
  specificity <- TN / (TN + FP)
  accuracy <- (TN + TP) / (TN + TP + FP + FN)
  
  print(t)
  
  print(paste("Sensitivity = ", sensitivity))
  print(paste("Specificify = ", specificity))
  print(paste("Accuracy =    ", accuracy))
}
