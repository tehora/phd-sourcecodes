#include <ghutils.h>
#include <algorithm>
#include <iomanip>
#include <math.h> 

//observations
int values[1000][10];

// averages
double ith_avg[1000];

int main(int argc, char **argv) {


   for (int i=0;i<1000; i++) {
       for (int j=0; j<10; j++) {
            values[i][j]=0;
        }
   }
    
    {
        int i = 0;
        csvparser in(argv[1], ';');
        while (in.next()) {
            for (int j =1; j<11; j++) {
                values[i][j-1] = tonum(in[j]);  
            }
            i++;
        }
    }

    cout << fixed <<setprecision(3); 
    
    for (int i = 0; i<10; i++) {
        double sum = 0;
        double sum_means = 0;
        //sum of all values
        for (int j = 0; j<1000; j++) {
            sum+=values[j][i];
        }
        //ith average
        for (int z=0;z<1000; z++) {
            ith_avg[z] = 0;
        }    
        for (int j = 0; j<1000; j++) {
            ith_avg[j] = (sum-values[j][i])/999;
            sum_means+= ith_avg[j];
        }
        cout <<"Distance " <<i <<" jackknife mean is: " << sum_means/1000 <<"\n";

        sort(ith_avg, ith_avg + 1000);
        cout <<"Distance " <<i <<" confidence interval for mean is: (" << ith_avg[50] <<";" << ith_avg[950] <<")"  <<"\n";
        cout <<"Distance " <<i <<" conf int diffs are: " << sum_means/1000-ith_avg[50] <<";" << ith_avg[950] - sum_means/1000  <<"\n";

        double sum_avgs = 0;
        for (int j = 0; j <1000; j++) {
            sum_avgs += (double(ith_avg[j] - sum_means/1000)*double(ith_avg[j] - sum_means/1000));
        }
        cout <<"Distance " <<i <<" std_dev is: " <<sqrt(sum_avgs*999/1000)  <<"\n";
        cout <<"Distance " <<i <<" std_dev/mean is: " <<100*(sqrt(sum_avgs*999/1000)/(sum_means/1000)) <<"%"  <<"\n";

    }    

}
