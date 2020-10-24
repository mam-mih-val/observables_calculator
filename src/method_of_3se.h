//
// Created by mikhail on 10/24/20.
//

#ifndef OBSERVABLESCALCULATOR_SRC_METHOD_OF_3SE_H_
#define OBSERVABLESCALCULATOR_SRC_METHOD_OF_3SE_H_

#include <utility>

#include <DataContainer.hpp>
#include <StatCalculate.hpp>

#include "file_manager.h"

class MethodOf3SE{
public:
  MethodOf3SE(const std::string &u_vector_name,
              const std::string &q_vector_name, const std::string &component,
              const std::vector<std::string> &resolution_q_vectors)
      : u_vector_name_(u_vector_name), q_vector_name_(q_vector_name),
        component_(component), resolution_q_vectors_(resolution_q_vectors) {}
  virtual ~MethodOf3SE() = default;
  void CalculateObservables();
  void SetUqDirectory(const std::string &uq_deirectory) {
    uq_directory_ = uq_deirectory;
  }
  void SetQqDirectory(const std::string &qq_directory) {
    qq_directory_ = qq_directory;
  }
  void SetUVectorName(const std::string &u_vector_name) {
    u_vector_name_ = u_vector_name;
  }
  void Write(){
    int i=0;
    for( auto  resolution: resolutions_){
      resolution.Write( std::data( "res_"+combinations_names_.at(i) ) );
      ++i;
    }
  }

private:
  Qn::DataContainer<Qn::StatCalculate> CalculateResolution(std::vector<Qn::DataContainerStatCalculate> correlations);
  std::vector<std::vector<std::pair<std::string, std::string>>> ConstructResolutionCombinations(std::string reff_q, std::vector<std::string> q_combination);
  Qn::DataContainer<Qn::StatCalculate> ReadContainerFromFile( const std::string&, const std::pair<std::string, std::string>& vectors );

  std::string uq_directory_;
  std::string u_vector_name_;
  std::string qq_directory_;
  std::string q_vector_name_;
  std::string component_;
  std::vector<std::string> resolution_q_vectors_;
  std::vector<std::string> combinations_names_;
  std::vector<Qn::DataContainer<Qn::StatCalculate>> resolutions_;
};

#endif // OBSERVABLESCALCULATOR_SRC_METHOD_OF_3SE_H_
