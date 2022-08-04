#include <iostream>
#include <cmath>
#include <string>
using namespace std;


// Yassa Seifen - 2001307 
// 31/5/2022

long double get_det (auto mat[10][10] , int size ) ;
void laplace_sub (auto mat[10][10],  auto temp[10][10] , int size , int row  , int column);

int main (){
    int rows_a,cols_a,rows_b,cols_b;
    int mat_a[10][10];
    int mat_b[10][10];

    // Asking for Dimensions
    cout<<"Please enter dimensions of Matrix A:" <<endl;
        cin >> rows_a >> cols_a;
    cout<<"Please enter dimensions of Matrix B:" <<endl;
        cin >> rows_b >> cols_b;

    // Getting the inner values of Matrices
    cout<<"Please enter values of Matrix A:"<<endl;
    for(int r=0;r<rows_a;r++){
        for(int c=0;c<cols_a;c++){
            cin >> mat_a[r][c];
        }
    }
    cout<<"Please enter values of Matrix B:"<<endl;
    for(int r=0;r<rows_b;r++){
        for(int c=0;c<cols_b;c++){
            cin >> mat_b[r][c];
        }
    }


    int sum_mat[rows_a][cols_a];
    int multi_mat[rows_a][cols_b];

    choose_section: 
    cout<<"Please choose operation type(1: A+B, 2: A-B, 3: AxB, 4: A*inverse(B), 5: |A|, 6: |B|, 7: quit):"<< endl;
        int choose;
        cin >> choose;

        switch (choose)
            {
            case 1:{
                if (rows_a==rows_b && cols_a==cols_b)
                {
                    for(int r=0;r<rows_a;r++){
                        for(int c=0;c<cols_a;c++){
                            sum_mat[r][c]=lround(mat_a[r][c]+mat_b[r][c]);
                        }
                    }
                    for(int r=0;r<rows_a;r++){
                        for(int c=0;c<cols_a;c++){
                            cout<< sum_mat[r][c]<<" ";
                        }
                        cout<<"\n";
                    }
                }
                else {
                    cout<<"The operation you chose is invalid for the given matrices."<<endl;
                }
                goto choose_section;}

            case 2:{
                if (rows_a==rows_b && cols_a==cols_b)
                {
                    for(int r=0;r<rows_a;r++){
                        for(int c=0;c<cols_a;c++){
                            sum_mat[r][c]=lround(mat_a[r][c]-mat_b[r][c]);
                        }
                    }
                    for(int r=0;r<rows_a;r++){
                        for(int c=0;c<cols_a;c++){
                            cout<< sum_mat[r][c]<<" ";
                            
                        }
                        cout<<"\n";
                    }
                }
                else {
                    cout<<"The operation you chose is invalid for the given matrices."<<endl;
                }
                goto choose_section; 
                } 

            case 3:{
                if (rows_b==cols_a)
                {   
                    for(int r=0;r<rows_a;r++){    
                        for(int c=0;c<cols_b;c++){    
                            multi_mat[r][c]=0;    
                                for(int z=0;z<cols_a;z++){    
                                    multi_mat[r][c]= multi_mat[r][c] + mat_a[r][z]*mat_b[z][c];    
                                }    
                        }    
                    }  
                    for(int r=0;r<rows_a;r++){
                        for(int c=0;c<cols_b;c++){
                            cout<< lround(multi_mat[r][c])<<" ";
                        }
                        cout<<"\n";
                    }
                }
                else {
                    cout<<"The operation you chose is invalid for the given matrices."<<endl;
                    }
                
                goto choose_section; }

            case 4 :{
                long double detb = get_det(mat_b,  rows_b); 
                if (detb == 0 ){
                      cout << "The operation you chose is invalid for the given matrices."<<endl;
  
                }
                else{
  
                    if (rows_b == cols_a && rows_b == cols_b){
                        double inverseb[10][10]  , AinverseB [10][10] , submat[10][10];
  
                        // Inverse calculation
                        for(int i=0 ; i< rows_b ; i++){
                            for(int j=0;j< rows_b;j++){
  
                            laplace_sub(mat_b,submat ,rows_b , i,j );
                            inverseb[j][i] = (pow(-1 , i+j)*(get_det(submat,rows_b-1)) )/ detb ;
                            }
                        }
  
                        // Multiply
                        for(int r=0;r<rows_a;r++){    
                            for(int c=0;c<cols_b;c++){    
                                AinverseB[r][c]=0;    
                                    for(int z=0;z<cols_a;z++){    
                                        AinverseB[r][c]= AinverseB[r][c] + mat_a[r][z]*inverseb[z][c];    
                                    }    
                            }    
                        } 
  
                        for(int r=0;r<rows_a;r++){
                            for(int c=0;c<cols_b;c++){
                                cout<< lround(AinverseB[r][c])<<" ";
                            }
                            cout<<"\n";
                        } 
                    }
  
                    else{
                        cout << "The operation you chose is invalid for the given matrices."<<endl; 
                        }
                }
                goto choose_section; 
            }  
            
            case 5:{
                if (rows_a == cols_a)
                {
                    long long int det_a = get_det(mat_a, rows_a); 
                    cout << det_a <<endl;
                }

                else{
                    cout << "The operation you chose is invalid for the given matrices."<<endl;
                    }
                    goto choose_section;}
        
            case 6:{

                if (rows_b == cols_b)
                {

                    long long int det_b = get_det(mat_b,  rows_b); 
                    cout << det_b <<endl;

                }

                else {
                    cout << "The operation you chose is invalid for the given matrices."<<endl;
                    }
                goto choose_section;      }

            case 7:
                cout << "Thank you!"<<endl;
                return 0;    

            default:
                cout << "The operation you chose is invalid for the given matrices."<<endl;
                goto choose_section;
            }
}

// based on Laplace Expansion
void laplace_sub (auto mat[10][10],  auto temp[10][10] , int size , int row  , int column){
    int row_ed = 0 , col_ed = 0  ; 

    for (int r = 0;  r < size ; r++){
        for (int c = 0 ; c < size ; c++){
            if (c != column && r != row){

                temp[row_ed][col_ed] = mat[r][c]  ;
                    col_ed ++ ;

                    if  (col_ed == size-1){

                        col_ed = 0;
                        row_ed ++ ; 
                    }
            }
        }
    }
}


long double get_det (auto mat[10][10] , int size ){
    long double det = 0 ;

    if (size == 1){
        return mat[0][0];
    }

    else if  (size == 2){
        long double cross1, cross2;
        cross1 = mat[0][0]*mat[1][1];
        cross2 = mat[1][0]*mat[0][1];
        det = cross1 - cross2;
        return det; 
    }

    else if (size == 3)
    {

        long double m,n,o;
        m = mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1];
        n = mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0];
        o = mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0];

        det = (m * mat[0][0]) - (n * mat[0][1]) + (o * mat[0][2]);

        return det;
    }

    else {

        int submat_temp[10][10]; 
        for(int m = 0 ; m < size ; m++)
        {
            laplace_sub(mat ,submat_temp ,size ,0 ,m ) ;
            det = det + mat[0][m]*get_det(submat_temp , size-1) * pow(-1 , m);
        }
        return det ;
    }
    
}
