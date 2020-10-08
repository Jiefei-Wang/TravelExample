#include <Rcpp.h>
#include "Travel/Travel.h"
using namespace Rcpp;

struct Seq_info{
  size_t start;
  size_t step;
  ~Seq_info(){
    Rprintf("I am called from GC\n");
  }
};

// The data reading function
size_t read_sequence(const Travel_altrep_info* altrep_info, void *buffer, size_t offset, size_t length)
{
  Seq_info* info = (Seq_info*)altrep_info->private_data;
  for (size_t i = 0; i < length; i++)
  {
    ((double *)buffer)[i] = info -> start + info -> step * (offset + i);
  }
  return length;
}

// The main ALTREP making function
// [[Rcpp::export]]
SEXP make_sequence_altrep(size_t n, size_t start, size_t step)
{
  Seq_info* info = new Seq_info{start, step};
  Travel_altrep_info altrep_info = {};
  altrep_info.length = n;
  altrep_info.type = REALSXP;
  altrep_info.operations.get_region = read_sequence;
  altrep_info.private_data = info;
  altrep_info.protected_data = Rf_protect(Travel_shared_ptr<Seq_info>(info));
  SEXP x = Rf_protect(Travel_make_altptr(altrep_info));
  Rf_unprotect(2);
  return x;
}