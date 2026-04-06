// Macro for visualzing geometry using Eve
// Sham Kumar; shyam055119@gmail.com; shyam.kumar@ba.infn.it

void draw_geom(TString rootfilename = "detector_geometry.root")
{
	
  TEveManager::Create();
  gGeoManager = TGeoManager::Import(rootfilename); // or use TGeoManager::Import(rootfile)
  if (gGeoManager == nullptr) return;
  TEveGeoTopNode *TNod = new TEveGeoTopNode(gGeoManager,gGeoManager->GetTopNode()); // pass node here instead of topnode
  gEve->AddGlobalElement(TNod);
  gEve->FullRedraw3D(kTRUE);

}


