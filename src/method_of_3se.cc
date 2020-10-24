//
// Created by mikhail on 10/24/20.
//

#include "method_of_3se.h"

Qn::DataContainer<Qn::StatCalculate> MethodOf3SE::CalculateResolution(std::vector<Qn::DataContainerStatCalculate> correlations){
  auto result = Sqrt(correlations.at(0) * correlations.at(1) / correlations.at(2) ) * sqrt(2.0);
  return result;
}

void MethodOf3SE::CalculateObservables(){
  auto combinations = ConstructResolutionCombinations(q_vector_name_, resolution_q_vectors_);
  std::vector<Qn::DataContainer<Qn::StatCalculate>> results;
  for( auto res_combination_names : combinations ){
    std::vector<Qn::DataContainer<Qn::StatCalculate>> set_for_res_calc;
    set_for_res_calc.push_back( ReadContainerFromFile( qq_directory_, res_combination_names.at(0) ) );
    set_for_res_calc.push_back( ReadContainerFromFile( qq_directory_,  res_combination_names.at(1) ) );
    set_for_res_calc.push_back( ReadContainerFromFile(  qq_directory_, res_combination_names.at(2) ) );
    combinations_names_.push_back( q_vector_name_+" ( "+res_combination_names.at(2).first+" , "+res_combination_names.at(2).second+" )" );
    resolutions_.push_back( CalculateResolution( set_for_res_calc ) );
  }
}

std::vector<std::vector<std::pair<std::string, std::string>>> MethodOf3SE::ConstructResolutionCombinations(
    std::string reff_q, std::vector<std::string> q_combination){
  auto q1 = std::move(reff_q);
  std::vector<std::vector<std::pair<std::string, std::string>>> combinations;
  for (size_t i=0; i<q_combination.size(); ++i ){
    auto q2 = q_combination.at(i);
    for( size_t j=i+1; j<q_combination.size(); ++j ){
      auto q3 = q_combination.at(j);
      std::vector<std::pair<std::string,std::string>> combination;
      combination.emplace_back(q1, q2);
      combination.emplace_back(q1, q3);
      combination.emplace_back(q2, q3);
      combinations.push_back(combination);
    }
  }
  return combinations;
}

Qn::DataContainer<Qn::StatCalculate> MethodOf3SE::ReadContainerFromFile( const std::string& directory, const std::pair<std::string, std::string>& vectors  ){
  Qn::DataContainerStatCollect*  obj;
  auto name = directory+"/"+vectors.first+"."+vectors.second+"."+component_;
  try {
    obj = FileManager::GetObject<Qn::DataContainerStatCollect>(name);
  }catch( std::runtime_error& ){
    name = vectors.second+"."+vectors.first+"."+component_;
    FileManager::GetObject<Qn::DataContainerStatCollect>(name);
  }
  auto result = Qn::DataContainerStatCalculate(*obj);
  result.SetErrors(Qn::StatCalculate::ErrorType::BOOTSTRAP);
  return result;
}

