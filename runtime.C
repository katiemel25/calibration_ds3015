/* Code to calculate run time with certain cuts on run number*/ 


Cuore::QGlobalDataManager dm;
dm.SetOwner("CuoreMetaData");
QRunsManagerHandle runMgrHdl("RunsManager");
runMgrHdl.GetOnlyGoodRuns(true);
runMgrHdl.AddDataset(3018);
dm.Get(&runMgrHdl,"DB");
const RunsManager runs = runMgrHdl.Get();
double runtime = runs.GetCalibrationRunTime();

  

Cuore::QGlobalDataManager dm;
dm.SetOwner("CuoreMetaData");
QRunsManagerHandle runMgrHdl("RunsManager");
runMgrHdl.GetOnlyGoodRuns(true);
runMgrHdl.AddDataset(3018);
dm.Get(&runMgrHdl,"DB");
const RunsManager runs = runMgrHdl.Get();
const std::vector< const RunsClass * > runsclasses = runs.GetListOfCalibrationRuns();
for (int i = 0; i < runsclasses.size(); ++i) {std::cout << "Run number: " << runsclasses[i]->GetRunNumber() << ", End time: " << runsclasses[i]->GetEndRunUnixTime() << std::endl;}



Cuore::QGlobalDataManager dm;
dm.SetOwner("CuoreMetaData");
QRunsManagerHandle runMgrHdl("RunsManager");
runMgrHdl.GetOnlyGoodRuns(true);
runMgrHdl.AddDataset(3018);
dm.Get(&runMgrHdl,"DB");
const RunsManager runs = runMgrHdl.Get();
const std::vector< const RunsClass * > runsclasses = runs.GetListOfCalibrationRuns();
for (int i = 0; i < runsclasses.size(); ++i) {std::cout << "Run number: " << runsclasses[i]->GetRunNumber() << ", Run time: " << runsclasses[i]->GetRunTime() << std::endl;}



Run number: 301190, Run time: 36944
Run number: 301191, Run time: 40760
Run number: 301193, Run time: 75399
Run number: 301195, Run time: 78040
