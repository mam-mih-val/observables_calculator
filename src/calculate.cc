//
// Created by mikhail on 10/23/20.
//

#include "file_manager.h"
#include "method_of_3se.h"

int main(){
  FileManager::OpenFile( "~/Correlations/new_qn_analysis.root" );
  MethodOf3SE test_x = MethodOf3SE( "u_RESCALED",
                                 "W1_RESCALED",
                                 "x1x1",
                                 {
                                     "W2_RESCALED",
                                     "W3_RESCALED",
//                                     "M_RESCALED",
                                 } );
  MethodOf3SE test_y = MethodOf3SE( "u_RESCALED",
                                 "W1_RESCALED",
                                 "y1y1",
                                 {
                                     "W2_RESCALED",
                                     "W3_RESCALED",
//                                     "M_RESCALED",
                                 } );
  test_x.SetQqDirectory("/QQ/SP");
  test_x.SetUqDirectory("/uQ/SP");
  test_y.SetQqDirectory("/QQ/SP");
  test_y.SetUqDirectory("/uQ/SP");
  test_x.CalculateObservables();
  test_y.CalculateObservables();
  auto file_out = TFile::Open("out.root", "recreate");
  file_out->cd();
  test_x.Write();
  test_y.Write();
  file_out->Close();
  return 0;
}