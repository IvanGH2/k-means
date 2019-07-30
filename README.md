# k-means
Simple template based k-means implementation (for 2D data)

kmeans is a simple k-means algorithm implementation based on the Java solution found here (http://mnemstudio.org/clustering-k-means-example-1.htm). 
Certain things are, however, slightly changed to make the code more efficient and my c++ code is template based.

The typical usage is as follows

    //vectors vf1 and vf2 respectively represent the input data	(they both represent one data set, with vf1 denoting
    //x values and vf2 y values so the input is { {1,0}, {3,4}, {5,7}, {3.5,5}, {4.5,5}, {1.5,2}, {3.5,4.5} }
    
    std::vector<float> vf1;

    vf1.push_back(1.0f);
    vf1.push_back(3.0f);
    vf1.push_back(5.0f);
    vf1.push_back(3.5f);
    vf1.push_back(4.5f);
    vf1.push_back(1.5f);
    vf1.push_back(3.5f);

    std::vector<float> vf2;

    vf2.push_back(1.0f);
    vf2.push_back(4.0f);
    vf2.push_back(7.0f);
    vf2.push_back(5.0f);
    vf2.push_back(5.0f);
    vf2.push_back(2.0f);
    vf2.push_back(4.5f);
    //init the k-means with 2 clusters
    KMeansResult<float, float> km_f(2);
    km_f.SetNumDataPoints(vf1.size());

    km_f.InitCentroids(1.0f,1.0f); //init the first centroid
    km_f.InitCentroids(5.0f,7.0f); //init the second centroid

    km_f.InitDatax(&vf1);
    km_f.InitDatay(&vf2);

    km_f.GenerateClusters(); 
    //results
    const std::vector<unsigned> &vc=km_f.GetClusterData();
    int size = vc.size();
    for(int i=0;i<vc.size();i++){
        std::cout << vc[i] << std::endl;
    }
    const std::vector<DATAPOINT<float,float> > &vcd=km_f.GetCentroidValues();
    
    for(int i=0;i<vcd.size();i++){
        const DATAPOINT<float,float> *d=&vcd[i];
        std::cout << d->a << "  " << d->b << std::endl;
    }

Or alternatively, just put everything in a single vector

    std::vector<DATAPOINT<float,float> > vf; //this holds the input data
    vf.push_back(DATAPOINT<float,float>(1.0f,1.0f));
    vf.push_back(DATAPOINT<float,float>(3.0f,4.0f));
    vf.push_back(DATAPOINT<float,float>(5.0f,7.0f));
    vf.push_back(DATAPOINT<float,float>(3.5f,5.0f));
    vf.push_back(DATAPOINT<float,float>(4.5f,5.0f));
    vf.push_back(DATAPOINT<float,float>(1.5f,2.0f));
    vf.push_back(DATAPOINT<float,float>(3.5f,4.5f));
    
     KMeansResult<float, float> km_f(2);//2 clusters
    km_f.SetNumDataPoints(vf.size());//number of input data

    km_f.InitCentroids(DATAPOINT<float,float>(1.0f,1.0f)); //init the first centroid/cluster
    km_f.InitCentroids(DATAPOINT<float,float>(5.0f,7.0f)); //init the second centroid/cluster

    km_f.InitData(&vf);

    km_f.GenerateClusters(); 

The k-means algorithm is not guaranteed to find a final solution. The results also depend on the initial values of clusters
as well as on the number thereof.

This code is not thouroughly tested so use it at your own risk. You're free, however, to use and modify this code
in any way you see fit since there's no licence associated with it.
