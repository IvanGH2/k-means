#ifndef KMEANS_H
#define KMEANS_H

#include <vector>
#include<iostream>
#include "math.h"


template <class T, class U>
struct DATAPOINT{

            T a;
			
            U b;
			
            DATAPOINT(T a,U b) : a(a), b(b){}
			
            DATAPOINT(){}
};

template <class X, class Y>
class KMeansResult{

                unsigned numClusters, numDataPoints;

                std::vector<DATAPOINT<X,Y> > vCentroids;
				
                std::vector<X> *vX;
				
                std::vector<Y> *vY;
				
                std::vector<unsigned> vClusterData;

public:

                KMeansResult(){}

                KMeansResult(unsigned nClusters) : numClusters(nClusters){}

                void SetNumClusters(unsigned nClusters) { numClusters = nClusters; }

                void SetNumDataPoints(unsigned nDataPoints) { numDataPoints = nDataPoints; }

                void InitCentroids(X a, Y b){

                    vCentroids.push_back(DATAPOINT<X,Y>(a,b));
                }

                void InitDatax( std::vector<X> * pVx){ vX = pVx; }

                void InitDatay( std::vector<Y> * pVy){ vY = pVy; }

                void GenerateClusters(){

                    bool done = false;
                    const float largeVal = 100000000.0f;
                    float min;
                    unsigned currCluster = 0;

                    X distance=0;
         
                    vClusterData.resize(numDataPoints);

                    for(int i=0;i<numDataPoints;i++){
                        min = largeVal;
                        for(int j=0;j<numClusters;j++){
                            distance = ComputeDistance((*vX)[i],(*vY)[i],vCentroids[j]);
                            if(distance<min){
                                min=distance;
                                currCluster=j;
          
                            }
                        }

                        vClusterData[i] = currCluster;

                      //recalculate centroid values
                        int k = i+1;
                        for(int ii=0;ii<numClusters;ii++){
                            unsigned totalClustersX = 0, totalClustersY = 0;
                            unsigned totalPointsInCluster = 0;
                            for(int j=0;j<k;j++){

                                if(vClusterData[j]==ii){
                                    totalClustersX += (*vX)[j];
                                    totalClustersY += (*vY)[j];
                                    ++totalPointsInCluster;
                                }
                            }//end numdataPoints
                            if(totalPointsInCluster>0){
                                DATAPOINT<X,Y> *pD = &vCentroids[ii];
                                pD->a = totalClustersX/totalPointsInCluster;
                                pD->b = totalClustersY/totalPointsInCluster;
                            
                            }

                        }//end recalculate centroid values
                       }//end numDataPoints

                        while(!done){

                            for(int i=0;i<numClusters;i++){
                                unsigned totalClustersX = 0, totalClustersY = 0;
                                unsigned totalPointsInCluster = 0;
                                for(int j=0;j<numDataPoints;j++){

                                    if(vClusterData[j]==i){
                                        totalClustersX += (*vX)[j];
                                        totalClustersY += (*vY)[j];
                                        ++totalPointsInCluster;
                                    }
                                }//end numdataPoints
                                if(totalPointsInCluster>0){
                                    DATAPOINT<X,Y> *pD = &vCentroids[i];
                                    pD->a = totalClustersX/totalPointsInCluster;
                                    pD->b = totalClustersY/totalPointsInCluster;
                                }
                            }
                            done = true;
                            for(int i=0;i<numDataPoints;i++){
                                min = largeVal;

                                for(int j=0;j<numClusters;j++){
                                    distance = ComputeDistance((*vX)[i],(*vY)[i], vCentroids[j]);
                                    if(distance<min){
                                        min=distance;
                                        currCluster=j;
                                }
                            }//end numClusters

                            vClusterData[i]     = currCluster;

                            if(vClusterData[i] != currCluster){
                                vClusterData[i] = currCluster;
                                done = false;
                            }
                        }
                    }//end done
                }
                inline X ComputeDistance(X x, Y y, DATAPOINT<X,Y> &dP){

                    Y ty = dP.b-y;
                    X tx = dP.a-x;
                    return sqrt(ty*ty+tx*tx);
                }
                const std::vector<DATAPOINT<X,Y> > &GetCentroidValues() const { return vCentroids; }

                const std::vector<unsigned> &GetClusterData() const { return vClusterData; }


               template<class T, class U>
               static void PrintClusters(const KMeansResult<T,U> &kMeans);

               template<class T, class U>
               friend void PrintClusters(const KMeansResult<T,U> &kMeans);


};

template <class T,class U>
void PrintClusters(const KMeansResult<T,U> &kMeans) {

         const std::vector<DATAPOINT<T,U> > &v = kMeans.vCentroids;
           for(int i=0;i<v.size();i++){

                               DATAPOINT<T,U> *c = &v.at(i);

                               std::cout << c->a << "      " << c->b << std::endl;
                              // std::cout << a; << "      " << b << std::endl;

               }

}

#endif // KMEANS_H



	
