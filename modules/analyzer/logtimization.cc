/**
 * The ARTist Project (https://artist.cispa.saarland)
 *
 * Copyright (C) 2017 CISPA (https://cispa.saarland), Saarland University
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @author "Oliver Schranz <oliver.schranz@cispa.saarland>"
 * @author "Sebastian Weisgerber <weisgerber@cispa.saarland>"
 *
 */

#include "runtime.h"

#include "logtimization.h"
#include "optimizing/artist/env/analyzer_environment.h"

using std::string;
using std::vector;
using std::shared_ptr;

namespace art {

HLogtimization::HLogtimization(HGraph* graph,
                               const DexCompilationUnit& _dex_compilation_unit,
                               CompilerDriver* _compiler_driver,
#ifdef BUILD_MARSHMALLOW
                               bool is_in_ssa_form,
#endif
                               const char* pass_name,
                               OptimizingCompilerStats* stats)
      : HArtist(graph
      , _dex_compilation_unit
      , _compiler_driver
#ifdef BUILD_MARSHMALLOW
      , is_in_ssa_form
#endif
    , pass_name, stats) {
  gLogVerbosity.artist = true;
  gLogVerbosity.artistd = true;
}

HLogtimization::~HLogtimization() { }

void HLogtimization::SetupModule() {
  const std::string& dex_name = ArtUtils::GetDexFileName(graph_);
  AnalyzerEnvironment& env = AnalyzerEnvironment::GetInstance();
  const std::vector<const DexFile*> dex_files;
  env.SetupEnvironment(dex_files, dex_name, graph_->GetDexFile(), nullptr, nullptr);
}

void HLogtimization::RunModule() {
  CHECK(graph_ != nullptr);
  VLOG(artistd) << "<##########################################################>";

  const DexFile& dexFile = graph_->GetDexFile();
//  AnalyzerEnvironment& env = AnalyzerEnvironment::GetInstance();
//  ClassLinker* class_linker = Runtime::Current()->GetClassLinker();
//  mirror::DexCache* dexcache = nullptr;
//  dexcache = class_linker->FindDexCache(dexFile);

  const string& dexFilePath = dexFile.GetLocation();
  const string methodSignature = PrettyMethod(graph_->GetMethodIdx(), dexFile);

  VLOG(artistd) << "Method: " << methodSignature << " (Dexfile: " << dexFilePath << ")";
  VLOG(artistd) << dexFile;
  const uint32_t class_count = dexFile.NumClassDefs();
  const uint32_t field_count = dexFile.NumFieldIds();
  const uint32_t method_count = dexFile.NumMethodIds();
  const uint32_t proto_count = dexFile.NumProtoIds();
  const uint32_t string_count = dexFile.NumStringIds();
  const uint32_t type_count = dexFile.NumTypeIds();

  VLOG(artistd) << "C: " << class_count << " "
                << "F: " << field_count << " "
                << "M: " << method_count << " "
                << "P: " << proto_count << " "
                << "S: " << string_count << " "
                << "T: " << type_count;

  VLOG(artistd) << "</##########################################################>";
}

}  // namespace art
