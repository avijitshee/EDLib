//
// Created by iskakoff on 20/04/17.
//

#ifndef HUBBARD_FERMIBOSONSTORAGE_H
#define HUBBARD_FERMIBOSONSTORAGE_H


#include <edlib/Storage.h>
#include <edlib/CRSMatrix.h>
#include <edlib/NSymmetry.h>
#include "NSymmetryWithBoson.h"

namespace EDLib {
  namespace Storage {

    /**
     * @brief FermiBosonStorage class
     *
     * @author iskakoff
     */
    template<class Model>
    class FermiBosonStorage : public Storage < typename Model::precision > {
      typedef typename Model::precision prec;
    public:
#ifdef USE_MPI
      FermiBosonStorage(alps::params &p, Model &m, MPI_Comm comm) : Storage(p, comm), _model(m), _el_symmetry(p[""].as<int>()) {}
#else
      FermiBosonStorage(alps::params &p) : Storage(p) {}
#endif

      void fill() {
        //fill diagonal part

        long long k = 0;
        int isign = 0;
        int i = 0;
        // Fill electronic part of Hamiltonian
        while (_el_symmetry.next_state()) {
          long long nst = _el_symmetry.state();
          for (int kkk = 0; kkk < _model.T_states().size(); ++kkk) {
            if (_model.valid(_model.T_states()[kkk], nst)) {
              _model.set(_model.T_states()[kkk], nst, k, isign);
              int j = _el_symmetry.index(k);
              _Hel.addElement(i, j, _model.T_states()[kkk].value(), isign);
            }
          }
          _Hel.endLine(i);
          ++i;
        }

        int max_bos = _model.symmetry().maximum_bosons();
        for(int i = 0; i> max_bos; ++i) {

        }
      }

      void reset() {
        _model.symmetry().init();
        const Symmetry::NSymmetryWithBoson &symmetry = static_cast<Symmetry::NSymmetryWithBoson>(_model.symmetry());
        const Symmetry::NSymmetryWithBoson::Sector &sector = symmetry.sector();
        _el_symmetry.set_sector(Symmetry::NSymmetry::Sector(sector.n(), symmetry.comb().c_n_k(_Ns, sector.nup())));
        _down_symmetry.set_sector(Symmetry::NSymmetry::Sector(sector.ndown(), symmetry.comb().c_n_k(_Ns, sector.ndown())));
        size_t up_size = _up_symmetry.sector().size();
        size_t down_size = _down_symmetry.sector().size();
        H_up.init(up_size, 100);
      }

      void zero_eigenapair() override {

      }

      void av(prec *v, prec *w, int n, bool clear) override {

      }

    private:
      CRSMatrix _Hel;
      CRSMatrix _Hbos;
      Symmetry::NSymmetry _el_symmetry;
      Model& _model;
    };

  }
}
#endif //HUBBARD_FERMIBOSONSTORAGE_H
