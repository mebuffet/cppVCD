/*
 * Copyright (c) 2013-2013 Wei Song <songw@cs.man.ac.uk> 
 *    Advanced Processor Technologies Group, School of Computer Science
 *    University of Manchester, Manchester M13 9PL UK
 *
 *    This source code is free software; you can redistribute it
 *    and/or modify it in source code form under the terms of the GNU
 *    General Public License as published by the Free Software
 *    Foundation; either version 2 of the License, or (at your option)
 *    any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

/* 
 * const range for VCD database
 * 02/07/2013   Wei Song
 *
 *
 */

#include "crange.hpp"

using namespace vcd;
using std::pair;
using std::vector;

VRange& vcd::VRange::operator+ (const VRange& rhs) {
  if(v.size() == 0)
    v = rhs.v;
  else if(rhs.v.size() > 0)
    combine(rhs.v);

  return *this;
}

void vcd::VRange::combine(const vector<pair<long> >& rhs) {
  BOOST_FOREACH(const vrange_type& vr, rhs) {
    combine(vr);
  }
}

void vcd::VRange::combine(const pair<long>& rhs) {
  vector<pair<long> >::iterator it = v.begin();
  it += search(rhs);
  // todo
}

unsigned int vcd::VRange::search(const pair<long>& rhs) const {
  unsigned int s = v.size();
  unsigned int i = 0;
  unsigned int j = s/2;
  unsigned int k = s-1;

  while(true) {
    if(v[j].first > rhs.first && rhs.first >= v[k].first) {
      i = j;
      j = (i + k + 1)/2;
      continue;
    } else if(rhs.first > v[j].first && v[i].first >= rhs.first) {
      k = j;
      j = (i + k)/2;
      continue;
    }
    return j;
  }
}
