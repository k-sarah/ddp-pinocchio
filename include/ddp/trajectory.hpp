#ifndef DDP_PINOCCHIO_TRAJECTORY_HPP_VQYVAKHAS
#define DDP_PINOCCHIO_TRAJECTORY_HPP_VQYVAKHAS

#include "ddp/internal/matrix_seq.hpp"

namespace ddp {

template <typename T>
struct Trajectory {
	static_assert(!std::is_const<T>::value, "");

	using Seq = internal::MatSeq<T, colvec>;
	struct Layout {
		Seq x;
		Seq u;
	} self;
	explicit Trajectory(Layout l) : self{VEG_FWD(l)} {}

	Trajectory(idx::Idx<colvec> x, idx::Idx<colvec> u)
			: self{Seq{VEG_FWD(x)}, Seq{VEG_FWD(u)}} {
		VEG_ASSERT_ALL_OF( //
				(x.index_begin() == u.index_begin()),
				(x.index_end() == u.index_end() + 1));
	}

	auto index_begin() const -> i64 { return self.u.index_begin(); }
	auto index_end() const -> i64 { return self.u.index_end(); }

	auto operator[](i64 t) const
			-> Tuple<View<T const, colvec>, View<T const, colvec>> {
		return {direct, self.x[t], self.u[t]};
	}
	auto operator[](i64 t) -> Tuple<View<T, colvec>, View<T, colvec>> {
		return {direct, self.x[t], self.u[t]};
	}
	auto x(i64 t) -> View<T, colvec> { return {self.x[t]}; }
	auto x(i64 t) const -> View<T const, colvec> { return {self.x[t]}; }
	auto u(i64 t) -> View<T, colvec> { return {self.u[t]}; }
	auto u(i64 t) const -> View<T const, colvec> { return {self.u[t]}; }
	auto x_f() const -> View<T const, colvec> {
		return self.x[self.x.index_end() - 1];
	}
	auto x_f() -> View<T, colvec> { return self.x[self.x.index_end() - 1]; }
};

} // namespace ddp

#endif /* end of include guard DDP_PINOCCHIO_TRAJECTORY_HPP_VQYVAKHAS */
