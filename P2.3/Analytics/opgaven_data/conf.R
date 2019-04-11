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
setwd("D:/GitHub/School/P2.3/Analytics/opgaven_data")

conf3 <- function(n, d) 
{
  predicttest= predict (tree, newdata=testData, type="class")
  t=table(n, predicttest)
  
  T1=t[1]
  F1a=t[2]
  F1b=t[3]
  F2a=t[4]
  T2=t[5]
  F2b=t[6]
  F3a=t[7]
  F3b=t[8]
  T3=t[9]
  
  sensitivity0 <- T1 / (T1 + F1a + F1b)
  specificity0 <- (T2 + T3) / (T2 + T3 + F2a + F3a)
  sensitivity2 <- T2 / (T2 + F2a + F2b)
  specificity2 <- (T1 + T3) / (T1 + T3 + F1a + F3a)
  sensitivity4 <- T3 / (T3 + F3a + F3b)
  specificity4 <- (T2 + T1) / (T2 + T1 + F2a + F1a)
  accuracy <- (T1 + T2 + T3) / (T1 + T2 + T3 + F1a + F1b + F2a + F2b + F3a + F3b)
  
  print(t)
  
  print(paste("Sensitivity 0 = ", sensitivity0))
  print(paste("Specificify 0 = ", specificity0))
  print(paste("Sensitivity 2 = ", sensitivity2))
  print(paste("Specificify 2 = ", specificity2))
  print(paste("Sensitivity 4 = ", sensitivity4))
  print(paste("Specificify 4 = ", specificity4))
  print(paste("Accuracy =    ", accuracy))
}
