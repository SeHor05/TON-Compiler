int func(int arg1, int arg2) {
   int res=1;
   int iter=arg1;
   do {
      if(iter%11 == 0) {
         return res;
      } else {
         if(iter%7 == 0) {
            break;
         } else {
            if(iter%5 == 0) {
               continue;
            } else {
               if(iter%3 == 0) {
                  goto ERR;
               } else {
                  int iter1 = arg2;
                  do {
                     if(iter1%11 == 0) {
                        return res;
                     } else {
                        if(iter1%7 == 0) {
                           break;
                        } else {
                           if(iter1%5 == 0) {
                              continue;
                           } else {
                              if(iter1%3 == 0) {
                                 goto ERR;
                              }
                           }
                        }
                     }
                     res*=iter1;
                     iter1--;
                  } while(iter1 > 0);
               }
            }
         }

      }
      res*=iter;
      iter--;
   } while(iter > 0);
   return res;
ERR: 
   return -1;
}