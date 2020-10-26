//
// Created by mikhail on 10/25/20.
//

#include "method.h"

Qn::DataContainer<Qn::StatCalculate> Method::ReadContainerFromFile( const std::string& directory, const std::pair<VectorConfig, VectorConfig>& vectors ){
  Qn::DataContainerStatCollect*  obj;
  auto name = directory+"/"+vectors.first.name+"."+vectors.second.name+"."+vectors.first.component_name+vectors.second.component_name;
  try {
    obj = FileManager::GetObject<Qn::DataContainerStatCollect>(name);
  }catch( std::runtime_error& ){
    name = vectors.second.name+"."+vectors.first.name+"."+vectors.second.component_name+vectors.first.component_name;
    FileManager::GetObject<Qn::DataContainerStatCollect>(name);
  }
  auto result = Qn::DataContainerStatCalculate(*obj);
  result.SetErrors(Qn::StatCalculate::ErrorType::BOOTSTRAP);
  return result;
}

