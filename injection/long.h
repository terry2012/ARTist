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

#ifndef ART_INJECTION_LONG_H_
#define ART_INJECTION_LONG_H_

#include "primitives.h"

namespace art {

class Long : public Primitives {
 public:
  Long()
      : value(0) {}

  explicit Long(const int64_t _value)
      : value(_value) {}

  int64_t GetValue() const {
    return this->value;
  }

  virtual ~Long() {}

  virtual ParameterType GetType() const {
    return ParameterType::tLong;
  }

 private:
  // 64bit Java Integer: https://docs.oracle.com/javase/tutorial/java/nutsandbolts/datatypes.html
  int64_t value;
};

}  // namespace art

#endif  // ART_INJECTION_LONG_H_
