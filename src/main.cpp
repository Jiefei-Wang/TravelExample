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
size_t read_sequence(filesystem_file_data &file_data, void *buffer, size_t offset, size_t length)
{
  Seq_info* info = (Seq_info*)file_data.private_data;
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
  SEXP smart_ptr = Rf_protect(Travel_shared_ptr<Seq_info>(info));
  SEXP x = Rf_protect(Travel_make_altptr(REALSXP, n, read_sequence, info, smart_ptr));
  Rf_unprotect(2);
  return x;
}