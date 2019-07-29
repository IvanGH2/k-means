# k-means
Simple template based k-means implementation

kmeans is a simple k-means algorithm implementation based on the Java solution found here. 
Certain things are, however, slightly changed to make the code more efficient and my c++ code is template based.

The typical usage is as follows

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

    KMeansResult<float, float> km_f(2);
    km_f.SetNumDataPoints(vf1.size());
    km_f.InitCentroids(1.0f,1.0f);
    km_f.InitCentroids(5.0f,7.0f);

    km_f.InitDatax(&vf1);
    km_f.InitDatay(&vf2);

    km_f.GenerateClusters();

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
