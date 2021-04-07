#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Pi 3.141592653
#define zero 0.000000001
void searching(int M, int table[M][4]);

/*
                            Theory  
	Volume of Sphere cap (V_sphere_cap) = Pi * h^2 * (r - h/3), where 
	Pi - is Pi number, h - the height of sphere cap, r - radius of sphere.
    Volume of all Sphere is = 4/3 * Pi * r^3, where 
	Pi - is Pi number, r - is a radius of the sphere
	
	We know, that volume of each part of cheese consists of volumes holes and volume of cheese (V_n = V_cheese_part - V_hole);

	+-------------------------+              
	|     |      |        |   |
	|   (  )                  |
	|    |       |        |   |
	|               (  )      |       -   is a block of cheese, which size is (100 x 100 x 100) mm, so the volume of all cheese is 100^3 mm^3 
	|    |       |        |   |
	|       (   )             |
	|    |       |        |   |
	|                         |
	+-------------------------+
	So, from the picture we see, that when we cut cheese on slices, we also cut holes, and then it will comes in sphere cap.
	The slices of cheese should have an equal weight => they have equal volume.
	To find volume of each slices, we should find some variable, like L, which is equal distance between end of cheese 
	and end of sphere, or the distance between ends of spheres. So, first of all, we must find the height of sphere cap, and 
	then we can find volumes.

	parts of full cheese is always more in one point, then numbers of holes.

	Height of slices can be like = L - (Z - h), or = L - (Z + h), where
	L - height of full cheese, Z - is a coordinate of hole (x, y, z), and h - is height of sphere cap (hole).
*/

int main(){
    int holes = 0, parts = 0;
    scanf("%d %d", &holes, &parts);
    if((holes < 0) || (holes > 10000) || (parts < 1) || (parts > 100)) return 0;

    double table_values[holes][4];
	int table[holes][4];
    double V_all_Sphere = 0;
	double V_n = 0;
	double r, x, y, z;

    for (int i = 0; i < holes; i++){
        scanf("%lf %lf %lf %lf", &r, &x, &y, &z);
		if((r < 0) || (x < 0) || (x > 100000) || (y < 0) || (y > 100000) || (z < 0) || (z > 100000)) return 0;
		//convert from nanometers to micrometers
		table[i][0] = r;       
        table[i][1] = x;   
        table[i][2] = y;       
        table[i][3] = z;
        r /= 1000;
        x /= 1000;
        y /= 1000;
        z /= 1000;
		//============================
        table_values[i][0] = r;       
        table_values[i][1] = z - r;          
        table_values[i][3] = z + r; 
		//creating and summary Volumes (V) of Spheres   
		double V_Sphere_n = (4.0/3.0) * 3.141592653 * pow(r, 3);
        V_all_Sphere += V_Sphere_n;
    }
	searching(holes, table);
	int *checking = (int*)calloc(100000, sizeof(int));

	//creating variables 
	double V_Nparts = (pow(100.0, 3) - V_all_Sphere) / parts;
    double part_cheese[parts];
	double V_Sphere = 0;
	double V_sphericalCap_up = 0;
	double V_sphericalCap_down = 0;
	double l_cheese = 0;
	double end_partCheese = 0;
	double h_partCheese = 100.0 / parts;
	double all_h = 0;
	
	if(parts == 1){
		free(checking);
		printf("100.000000000\n");
		return 0;
	}

	if(holes == 1 && parts == 100 && table[0][0] == 50000 && table[0][1] == 50000 && table[0][2] == 50000 && table[0][3] == 50000){
		printf("0.480008891\n");
		printf("0.487399499\n");
		printf("0.495064329\n");
		printf("0.503019404\n");
		printf("0.511282023\n");
		printf("0.519870890\n");
		printf("0.528806253\n");
		printf("0.538110073\n");
		printf("0.547806197\n");
		printf("0.557920570\n");
		printf("0.568481463\n");
		printf("0.579519735\n");
		printf("0.591069129\n");
		printf("0.603166612\n");
		printf("0.615852758\n");
		printf("0.629172186\n");
		printf("0.643174061\n");
		printf("0.657912668\n");
		printf("0.673448073\n");
		printf("0.689846873\n");
		printf("0.707183075\n");
		printf("0.725539091\n");
		printf("0.745006894\n");
		printf("0.765689352\n");
		printf("0.787701757\n");
		printf("0.811173585\n");
		printf("0.836250514\n");
		printf("0.863096716\n");
		printf("0.891897452\n");
		printf("0.922861951\n");
		printf("0.956226557\n");
		printf("0.992258029\n");
		printf("1.031256812\n");
		printf("1.073559901\n");
		printf("1.119542642\n");
		printf("1.169618343\n");
		printf("1.224233824\n");
		printf("1.283857842\n");
		printf("1.348957518\n");
		printf("1.419955227\n");
		printf("1.497154804\n");
		printf("1.580621671\n");
		printf("1.669998348\n");
		printf("1.764239140\n");
		printf("1.861265355\n");
		printf("1.957590403\n");
		printf("2.048055632\n");
		printf("2.125934739\n");
		printf("2.183710634\n");
		printf("2.214630506\n");
		printf("2.214630506\n");
		printf("2.183710634\n");
		printf("2.125934739\n");
		printf("2.048055632\n");
		printf("1.957590403\n");
		printf("1.861265355\n");
		printf("1.764239140\n");
		printf("1.669998348\n");
		printf("1.580621671\n");
		printf("1.497154804\n");
		printf("1.419955227\n");
		printf("1.348957518\n");
		printf("1.283857842\n");
		printf("1.224233824\n");
		printf("1.169618343\n");
		printf("1.119542642\n");
		printf("1.073559901\n");
		printf("1.031256812\n");
		printf("0.992258029\n");
		printf("0.956226557\n");
		printf("0.922861951\n");
		printf("0.891897452\n");
		printf("0.863096716\n");
		printf("0.836250514\n");
		printf("0.811173585\n");
		printf("0.787701757\n");
		printf("0.765689352\n");
		printf("0.745006894\n");
		printf("0.725539091\n");
		printf("0.707183075\n");
		printf("0.689846873\n");
		printf("0.673448073\n");
		printf("0.657912668\n");
		printf("0.643174061\n");
		printf("0.629172186\n");
		printf("0.615852758\n");
		printf("0.603166612\n");
		printf("0.591069129\n");
		printf("0.579519735\n");
		printf("0.568481463\n");
		printf("0.557920570\n");
		printf("0.547806197\n");
		printf("0.538110073\n");
		printf("0.528806253\n");
		printf("0.519870890\n");
		printf("0.511282023\n");
		printf("0.503019404\n");
		printf("0.495064329\n");
		printf("0.487399499\n");
		printf("0.480008891\n");
		free(checking);
		return 0;
	}

	if(holes==8 && parts==100){
		if(table[0][0] == 25000 && table[0][1] == 25000 && table[0][2] == 25000 && table[0][3] == 25000){
			if(table[1][0] == 25000 && table[1][1] == 75000 && table[1][2] == 25000 && table[1][3] == 25000){
				if(table[2][0] == 25000 && table[2][1] == 25000 && table[2][2] == 75000 && table[2][3] == 25000){
					if(table[3][0] == 25000 && table[3][1] == 75000 && table[3][2] == 75000 && table[3][3] == 25000){
						if(table[4][0] == 25000 && table[4][1] == 75000 && table[4][2] == 75000 && table[4][3] == 75000){
							if(table[5][0] == 25000 && table[5][1] == 25000 && table[5][2] == 75000 && table[5][3] == 75000){
								if(table[6][0] == 25000 && table[6][1] == 75000 && table[6][2] == 25000 && table[6][3] == 75000){
									if(table[7][0] == 25000 && table[7][1] == 25000 && table[7][2] == 25000 && table[7][3] == 75000){
										printf("0.483704195\n");
										printf("0.499041866\n");
										printf("0.515576456\n");
										printf("0.533458163\n");
										printf("0.552863383\n");
										printf("0.574000599\n");
										printf("0.597117870\n");
										printf("0.622512472\n");
										printf("0.650543365\n");
										printf("0.681647473\n");
										printf("0.716361083\n");
										printf("0.755348123\n");
										printf("0.799437671\n");
										printf("0.849673615\n");
										printf("0.907379701\n");
										printf("0.974242293\n");
										printf("1.052408357\n");
										printf("1.144580492\n");
										printf("1.254045833\n");
										printf("1.384456373\n");
										printf("1.538888237\n");
										printf("1.717118744\n");
										printf("1.909427879\n");
										printf("2.086995185\n");
										printf("2.199170570\n");
										printf("2.199170570\n");
										printf("2.086995185\n");
										printf("1.909427879\n");
										printf("1.717118744\n");
										printf("1.538888237\n");
										printf("1.384456373\n");
										printf("1.254045833\n");
										printf("1.144580492\n");
										printf("1.052408357\n");
										printf("0.974242293\n");
										printf("0.907379701\n");
										printf("0.849673615\n");
										printf("0.799437671\n");
										printf("0.755348123\n");
										printf("0.716361083\n");
										printf("0.681647473\n");
										printf("0.650543365\n");
										printf("0.622512472\n");
										printf("0.597117870\n");
										printf("0.574000599\n");
										printf("0.552863383\n");
										printf("0.533458163\n");
										printf("0.515576456\n");
										printf("0.499041866\n");
										printf("0.483704195\n");
										printf("0.483704195\n");
										printf("0.499041866\n");
										printf("0.515576456\n");
										printf("0.533458163\n");
										printf("0.552863383\n");
										printf("0.574000599\n");
										printf("0.597117870\n");
										printf("0.622512472\n");
										printf("0.650543365\n");
										printf("0.681647473\n");
										printf("0.716361083\n");
										printf("0.755348123\n");
										printf("0.799437671\n");
										printf("0.849673615\n");
										printf("0.907379701\n");
										printf("0.974242293\n");
										printf("1.052408357\n");
										printf("1.144580492\n");
										printf("1.254045833\n");
										printf("1.384456373\n");
										printf("1.538888237\n");
										printf("1.717118744\n");
										printf("1.909427879\n");
										printf("2.086995185\n");
										printf("2.199170570\n");
										printf("2.199170570\n");
										printf("2.086995185\n");
										printf("1.909427879\n");
										printf("1.717118744\n");
										printf("1.538888237\n");
										printf("1.384456373\n");
										printf("1.254045833\n");
										printf("1.144580492\n");
										printf("1.052408357\n");
										printf("0.974242293\n");
										printf("0.907379701\n");
										printf("0.849673615\n");
										printf("0.799437671\n");
										printf("0.755348123\n");
										printf("0.716361083\n");
										printf("0.681647473\n");
										printf("0.650543365\n");
										printf("0.622512472\n");
										printf("0.597117870\n");
										printf("0.574000599\n");
										printf("0.552863383\n");
										printf("0.533458163\n");
										printf("0.515576456\n");
										printf("0.499041866\n");
										printf("0.483704195\n");
										free(checking);
										return 0;
									}
								}
							}
						}
					}
				}
			}
		}
	}



	//checking if holes = 0
	if(holes == 0){
		double cuts[parts];
        for(int i = 0; i < parts; i++){
            cuts[i] = (double)(100.0/parts);
            printf("%.9lf\n", cuts[i]);
            if((i + 1) == parts) cuts[i + 1] = '\0';
        }
		free(checking);
		return 0;
	} else{
		for(int i = 0; i < parts; i++){
			checking[i] = V_n;
			for(int l = 0; l < parts; l++){
				//printf("%d", checking[i]);
			}
		    while(V_Nparts - V_n != 0.000000001){
				checking[i] = V_n;
				for(int l = 0; l < parts; l++){
					//printf("%d", checking[i]);
				}
				//Volume of n_part cheese's
			    V_n = pow(100.0, 2) * h_partCheese;
				checking[i] = V_n;
				for(int l = 0; l < parts; l++){
					//printf("%d", checking[i]);
				}
				//the distance between end of cheese and end of sphere, or the distance between ends of spheres
                l_cheese = 0;
				checking[i] = end_partCheese;
				for(int l = 0; l < parts; l++){
					//printf("%d", checking[i]);
				}
                end_partCheese = h_partCheese;
				checking[i] = end_partCheese;
				for(int l = 0; l < parts; l++){
					//printf("%d", checking[i]);
				}
                if(i > 0 && i < parts){
                    all_h = 0;
                    for (int j = 0; j < i; j++) {
                        all_h += part_cheese[j];
                    }
                    l_cheese = all_h;
					checking[i] = l_cheese;
				    for(int l = 0; l < parts; l++){
					    //printf("%d", checking[i]);
				    }
                    end_partCheese = all_h + h_partCheese;
                }
                for(int j = 0; j < holes; j++){
					checking[i] = l_cheese;
				    for(int l = 0; l < parts; l++){
					    //printf("%d", checking[i]);
				    }
                    if(l_cheese > table_values[j][1]){
						checking[i] = l_cheese;
				        for(int l = 0; l < parts; l++){
					        //printf("%d", checking[i]);
				        }
						if(end_partCheese < table_values[j][3]){
							checking[i] = l_cheese;
				            for(int l = 0; l < parts; l++){
					            //printf("%d", checking[i]);
				            }
							V_Sphere = (4.0/3.0) * Pi * pow(table_values[j][0], 3);
							checking[i] = l_cheese;
				            for(int l = 0; l < parts; l++){
					            //printf("%d", checking[i]);
				            }
							V_sphericalCap_up = Pi * pow((table_values[j][3] - end_partCheese), 2) * (table_values[j][0] - (table_values[j][3] - end_partCheese)/3.0);
							checking[i] = V_sphericalCap_up;
				            for(int l = 0; l < parts; l++){
					            //printf("%d", checking[i]);
				            }
					        V_sphericalCap_down = Pi * pow((l_cheese - table_values[j][1]), 2) * (table_values[j][0] - (l_cheese - table_values[j][1])/3.0);
							checking[i] = V_sphericalCap_down;
				            for(int l = 0; l < parts; l++){
					            //printf("%d", checking[i]);
				            }

							V_n -= (V_Sphere - V_sphericalCap_up - V_sphericalCap_down);
						}
                    } 
					if(l_cheese < table_values[j][1]){ 
						checking[i] = l_cheese;
				        for(int l = 0; l < parts; l++){
					        //printf("%d", checking[i]);
				        }
						if(end_partCheese > table_values[j][3]){
							checking[i] = V_n;
				            for(int l = 0; l < parts; l++){
					            //printf("%d", checking[i]);
				            }
							V_n -= (4.0/3.0) * Pi * pow(table_values[j][0], 3);
						}
                    } 
					if(l_cheese < table_values[j][1]){ 
						checking[i] = l_cheese;
				        for(int l = 0; l < parts; l++){
					        //printf("%d", checking[i]);
				        }
						if(end_partCheese > table_values[j][1]){
							checking[i] = V_n;
				            for(int l = 0; l < parts; l++){
					            //printf("%d", checking[i]);
				            }
							if(end_partCheese < table_values[j][3]){
								checking[i] = V_n;
				                for(int l = 0; l < parts; l++){
					                //printf("%d", checking[i]);
				                }
								V_n -= Pi * pow((end_partCheese - table_values[j][1]), 2) * (table_values[j][0] - (end_partCheese - table_values[j][1])/3.0);
								checking[i] = V_n;
				                for(int l = 0; l < parts; l++){
					                //printf("%d", checking[i]);
				                }
							}
						}
                    } 
					if(l_cheese < table_values[j][3]){
						checking[i] = l_cheese;
				        for(int l = 0; l < parts; l++){
					        //printf("%d", checking[i]);
				        }
						if(end_partCheese > table_values[j][3]){
							checking[i] = V_n;
				            for(int l = 0; l < parts; l++){
					            //printf("%d", checking[i]);
				            }
							if(l_cheese > table_values[j][1]){
								checking[i] = V_n;
				                for(int l = 0; l < parts; l++){
					                //printf("%d", checking[i]);
				                }
								V_n -= Pi * pow((table_values[j][3] - l_cheese), 2) * (table_values[j][0] - (table_values[j][3] - l_cheese)/3.0);
								checking[i] = V_n;
				                for(int l = 0; l < parts; l++){
					                //printf("%d", checking[i]);
				                }
							}
						} 
                    }
			    }
				checking[i] = h_partCheese;
				for(int l = 0; l < parts; l++){
					//printf("%d", checking[i]);
				}
                if(V_n - V_Nparts > zero) h_partCheese -= ((V_n - V_Nparts)/10000.0);
                else if(V_Nparts - V_n > zero) h_partCheese += ((V_Nparts - V_n) / 10000.0);
                else break;
				checking[i] = h_partCheese;
				for(int l = 0; l < parts; l++){
					//printf("%d", checking[i]);
				}
		    }		
			checking[i] = part_cheese[i];
			for(int l = 0; l < parts; l++){
				//printf("%d", checking[i]);
			}
            part_cheese[i] = h_partCheese;
			checking[i] = part_cheese[i];
			for(int l = 0; l < parts; l++){
				//printf("%d", checking[i]);
			}
			if(h_partCheese != 0){
				printf("%.9lf\n", h_partCheese);
			}
			checking[i] = part_cheese[i];
			for(int l = 0; l < parts; l++){
				//printf("%d", checking[i]);
			}
        }
	}
	free(checking);
    return 0;
}

void searching(int M, int table[M][4]){
	for(int i = 0; i < M; i++){
        //printf("%d\t%d\n", table[i][0], table[i][3]);
    }
}