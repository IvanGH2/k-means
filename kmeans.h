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

//template <class T, class U>

template <class X, class Y>
class KMeansResult{

                unsigned numClusters, numDataPoints;
                //X a; Y b;
                std::vector<DATAPOINT<X,Y> > vCentroids;
                std::vector<DATAPOINT<X,Y> > *vData;
                std::vector<X> *vX;
                std::vector<Y> *vY;
                std::vector<unsigned> vClusterData;
public:

                KMeansResult() :  vData(0){}
                KMeansResult(unsigned nClusters) : numClusters(nClusters), vData(0){}
                void SetNumClusters(unsigned nClusters) { numClusters = nClusters; }
                void SetNumDataPoints(unsigned nDataPoints) { numDataPoints = nDataPoints; }
                void InitCentroids(X a, Y b){
                    vCentroids.push_back(DATAPOINT<X,Y>(a,b));
                }
                void InitCentroids(DATAPOINT<X,Y> dp){
                    vCentroids.push_back(dp);
                }

                void InitData(std::vector<DATAPOINT<X,Y> > *p){
                    vData = p;
                }

                void InitDatax( std::vector<X> * pVx){ vX = pVx; }

                void InitDatay( std::vector<Y> * pVy){ vY = pVy; }
	
                void GenerateClusters(){
                    bool done = false;
                    const float largeVal = 100000000.0f;
                    float min;
                    unsigned currCluster = 0;
                    const bool twoDim = (vData && vData->size()>0) ? true : false;
			
                    X distance=0;
			
                    vClusterData.resize(numDataPoints);
			
                    for(int i=0;i<numDataPoints;i++){
                        min = largeVal;
                        for(int j=0;j<numClusters;j++){
                            if(twoDim)
                                distance = ComputeDistance((*vData)[i], vCentroids[j]);
                            else
                                distance = ComputeDistance((*vX)[i],(*vY)[i],vCentroids[j]);

                            if(distance<min){
                                min=distance;
                                currCluster=j;
                               // std::cout << "distance:" << " " << distance << std::endl;
                            }
                        }//end j<numClusters
                        vClusterData[i] = currCluster;
                      //recalculate centroid values
                        int k = i+1;
                        for(int ii=0;ii<numClusters;ii++){
                            unsigned totalClustersX = 0, totalClustersY = 0;
                            unsigned totalPointsInCluster = 0;
                            for(int j=0;j<k;j++){
                                if(vClusterData[j]==ii){
                                   if(twoDim){
                                       totalClustersX += (*vData)[j].a;
                                       totalClustersY += (*vData)[j].b;
                                   }else{
                                        totalClustersX += (*vX)[j];
                                        totalClustersY += (*vY)[j];
                                    }
                                    ++totalPointsInCluster;
                                }
                            }//end numdataPoints
                            if(totalPointsInCluster>0){
                                DATAPOINT<X,Y> *pD = &vCentroids[ii];
                                pD->a = totalClustersX/totalPointsInCluster;
                                pD->b = totalClustersY/totalPointsInCluster;
                              //  std::cout << "centr: " << ii << " " <<pD->a << "   " << pD->b << std::endl;
                            }
                        }//end recalculate centroid values
                       }//end numDataPoints
                        while(!done){
                            for(int i=0;i<numClusters;i++){
                                unsigned totalClustersX = 0, totalClustersY = 0;
                                unsigned totalPointsInCluster = 0;
                                for(int j=0;j<numDataPoints;j++){
                                    if(vClusterData[j]==i){
                                        if(twoDim){
                                            totalClustersX += (*vData)[j].a;
                                            totalClustersY += (*vData)[j].b;
                                        }else{
                                            totalClustersX += (*vX)[j];
                                            totalClustersY += (*vY)[j];
                                        }
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
                                    if(twoDim)
                                        distance = ComputeDistance((*vData)[i], vCentroids[j]);
                                    else
                                        distance = ComputeDistance((*vX)[i],(*vY)[i],vCentroids[j]);
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
                X ComputeDistance(X x, Y y, DATAPOINT<X,Y> &dP){
                    Y ty = dP.b-y;
                    X tx = dP.a-x;
                    return sqrt(ty*ty+tx*tx);
                }
                X ComputeDistance(DATAPOINT<X,Y> &dP0, DATAPOINT<X,Y> &dP1){
                    Y ty = dP1.b-dP0.b;
                    X tx = dP1.a-dP0.a;
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
//void PrintClusters(const KMeansResult<T,U> &kMeans);
#endif // KMEANS_H




	
