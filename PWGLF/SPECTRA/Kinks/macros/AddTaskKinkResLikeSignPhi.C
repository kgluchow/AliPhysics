AliResonanceKinkLikeSign *AddTaskKinkResLikeSignPhi(Short_t lCollidingSystems=0  /*0 = pp, 1 = AA*/)
{
// Creates, configures and attaches to the train a V0 check task.
   // Get the pointer to the existing analysis manager via the static access method.
   //==============================================================================
   AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
   if (!mgr) {
      ::Error("AddTaskKinkResonanceLikeSignPhi", "No analysis manager to connect to.");
      return NULL;
   }   

   // Check the analysis type using the event handlers connected to the analysis manager.
   //==============================================================================
   if (!mgr->GetInputEventHandler()) {
      ::Error("AddTaskKinkResonanceLikeSignPhi", "This task requires an input event handler");
      return NULL;
   }   
   TString type = mgr->GetInputEventHandler()->GetDataType(); // can be "ESD" or "AOD"
   if (type != "ESD") {
      ::Error("AddTaskKinkResonanceLikeSignPhi", "This task needs ESD input handler");
      return NULL;
   }   

   // Create and configure the task
	AliResonanceKinkLikeSign *taskkinkreslikesignPhi = new AliResonanceKinkLikeSign("TaskResLikeSignphi");
        taskkinkreslikesignPhi->SetPDGCodes(kKPlus, kKPlus);
        taskkinkreslikesignPhi->SetHistoSettings(70,0.99,1.088, 100, 0.0, 10.0);
        taskkinkreslikesignPhi->SetEtaLimits(-0.9, 0.9);
        taskkinkreslikesignPhi->SetMaxNsigmaToVertex(4.0);
        taskkinkreslikesignPhi->SetMaxDCAxy(3.0);
        taskkinkreslikesignPhi->SetMaxDCAzaxis(3.0);
        taskkinkreslikesignPhi->SetPtTrackCut(0.25);
        taskkinkreslikesignPhi->SetMinTPCclusters(50);
        taskkinkreslikesignPhi->SetMaxChi2PerTPCcluster(3.5);
        taskkinkreslikesignPhi->SetMaxCov0(2.0);
        taskkinkreslikesignPhi->SetMaxCov2(2.0);
        taskkinkreslikesignPhi->SetMaxCov5(0.5);
        taskkinkreslikesignPhi->SetMaxCov9(0.5);
        taskkinkreslikesignPhi->SetMaxCov14(2.0);
        taskkinkreslikesignPhi->SetMinKinkRadius(120.);
        taskkinkreslikesignPhi->SetMaxKinkRadius(220.);
        taskkinkreslikesignPhi->SetQtLimits(0.05, 0.5);
        taskkinkreslikesignPhi->SetUpperAbsEtaCut(0.9);

   mgr->AddTask(taskkinkreslikesignPhi);

   // Create ONLY the output containers for the data produced by the task.
   // Get and connect other common input/output containers via the manager as below
   //==============================================================================
   TString outputFileName = AliAnalysisManager::GetCommonFileName();
   outputFileName += ":PWG2KINKResonanceLikeSignPhi";
   if (lCollidingSystems) outputFileName += "_AA";
   else outputFileName += "_PP";
   if (mgr->GetMCtruthEventHandler()) outputFileName += "_MC";

   AliAnalysisDataContainer *coutput1 = mgr->CreateContainer("KinkResLikeSignPhi",
                                                             TList::Class(),
                                                             AliAnalysisManager::kOutputContainer,
                                                             outputFileName );

   mgr->ConnectInput(taskkinkreslikesignPhi, 0, mgr->GetCommonInputContainer());
   mgr->ConnectOutput(taskkinkreslikesignPhi, 1, coutput1);
   return taskkinkreslikesignPhi;
}   
