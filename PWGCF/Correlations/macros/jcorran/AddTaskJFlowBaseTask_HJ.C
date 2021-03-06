//_____________________________________________________________________
AliAnalysisTask *AddTaskJFlowBaseTask_HJ(TString taskName,TString JCatalystName, Bool_t isMC){
	// Load Custom Configuration and parameters
	// override values with parameters

	AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();

	//==== Set up di-hadron correlation jT task ====
	AliJFlowBaseTask *flowTask = new AliJFlowBaseTask(taskName.Data(),"AOD");
	flowTask->SetDebugLevel(5);
  flowTask->SetJCatalystTaskName(JCatalystName.Data());  // AliJCatalystTask has this name hard coded
	flowTask->SetIsMC(isMC);
	cout << flowTask->GetName() << endl;


	mgr->AddTask((AliAnalysisTask*) flowTask);

	// Create containers for input/output
	AliAnalysisDataContainer *cinput  = mgr->GetCommonInputContainer();


	// Connect input/output
	mgr->ConnectInput(flowTask, 0, cinput);
	AliAnalysisDataContainer *jHist = mgr->CreateContainer(Form("%scontainer",flowTask->GetName()),  TDirectory::Class(), AliAnalysisManager::kOutputContainer, Form("%s:%s",AliAnalysisManager::GetCommonFileName(), flowTask->GetName()));
	mgr->ConnectOutput(flowTask, 1, jHist );

	return flowTask;
}

