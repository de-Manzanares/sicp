/*
 * The acts of the mind, wherin it exerts its power over simple ideas, are
 * chiefly these three:
 * 1. Combining several ideas into one compound one, and thus all complex ideas
 * are made.
 * 2. The second is bringing two ideas, whether simple or complex, together, and
 * setting them by one another so as to take a view of them at once, without
 * uniting them into one, by which it gets all its ideas of relations.
 * 3. The third is separating them from all other ideas that ccompany them in
 * their real existence: this is called abstraction, and thus all its general
 * ideas are made.
 */

//***************** THE IDEA OF A COMPUTATIONAL PROCESS ************************

#include <cmath>
#include <iostream>

template <typename T> void println(T const &t) { std::cout << t << '\n'; }

template <typename T, typename... Types>
void println(T const &t, Types const &...args) {
  std::cout << t;
  println(args...);
}

/*
 * "percolate values upward" -- tree accumulation
 * environment(s) -- where the name object associations are stored
 * syntactic sugar -- coined by Peter Landin
 */

template <typename T> T square(T x) { return x * x; }

#define SQUARE_N
#ifdef SQUARE_Y

int main() {
  println(square(10));
  println(square(square(10)));
  return 0;
}
#endif

// TODO implement a scheme interpreter in C++ LOL

/*
 * normal-order evaluation -- fully expand then reduce
 * applicative-order evaluation -- evaluate arguments then apply
 * more dicussion on this later in the book
 */

//***************** EXERCISE 1.5

/*
 * (define (p) (p))
 * (define (test x y)
 *  (if (= x 0)
 *    0
 *    y))
 *
 * (test 0 (p))
 *
 * normal order:
 * (if (= 0 0)    ; predicate
 *    0           ; consequent
 *    (p))        ; alternative
 *
 * would return 0, because the predicate evaluates to true
 *
 * applicative order:
 * would result in an infinite loop as (p) is defined as (p)
 * ... hrm ..
 */

/*
 * declarative statements -- what is
 * imperative statements  -- how to
 */

//***************** EXAMPLE: SQUARE ROOTS BY NEWTON'S METHOD
/*
 * A special case of Newton's method, which is more general.
 * The algorithm to find square roots was developed by the Heron of Alexandria
 * in the first century AD
 * To approximate the root of x
 * Take guess y
 * Then improve it by averaging y with x/y
 */

auto abs(double const x) -> double { return x < 0 ? -x : x; }
auto is_good_enough(double const x, double const threshold) -> bool {
  return x < threshold;
}
auto improve_guess(double const y, double const x) -> double {
  return (y + x / y) * 0.5;
}
auto approximate_root(double const guess, double const x) -> double { // NOLINT
  if (is_good_enough(abs(square(guess) - x), 0.001)) {
    return guess;
  }
  return approximate_root(improve_guess(guess, x), x);
}

// this is much ... clearer ... and easier to express
// it's only possible because the language implementers have paved the way
// for us language users
std::size_t n_iterations{};
double approximate_root_ez(double const guess, double const x,
                           double const threshold) {
  auto approx = guess;
  while (std::abs(approx * approx - x) > threshold) { // NOLINT
    double const approx_old = approx;
    approx = 0.5 * (approx + x / approx);
    ++n_iterations;
    if (approx_old == approx) { // to handle case where threshold is too small
      break;
    }
  }
  return approx;
}

#define FIND_SQUARE_ROOTS_N
#ifdef FIND_SQUARE_ROOTS_Y

int main() {
  println(approximate_root(1.0, 2.0));
  println(approximate_root_ez(1.0, 2.0, 0), " calculated in ", n_iterations,
          " iterations ");
}

#endif

//***************** EXERCISE 1.8 NEWTON'S METHOD FOR CUBE ROOTS

/*
 * gives a guess y as the cube root of x
 * the following expression provides an improved guess
 * [(x/y^2) + 2y] / 3
 */

double approximate_cube_root(double const guess, double const x,
                             double const threshold) {
  auto approx = guess;
  while (std::abs(std::pow(approx, 3) - x) > threshold) { // NOLINT
    double const approx_old = approx;
    approx = (x / std::pow(approx, 2) + 2 * approx) / 3;
    ++n_iterations;
    if (approx_old == approx) {
      break;
    }
  }
  return approx;
}

#define FIND_CUBE_ROOT_N
#ifdef FIND_CUBE_ROOT_Y

int main() {
  println(approximate_cube_root(1.0, 2.0, 0), " calculated in ", n_iterations,
          " iterations");
  return 0;
}

#endif

/* linear recursive process - number of calls grows linearly with n
 * the expansion of this process builds up a chain of deferred operations
 * the chain begins to shrink only after we reach the base case
 */
std::size_t factorial_recursive(std::size_t const n) { // NOLINT
  if (n == 1) {
    return 1;
  }
  return n * factorial_recursive(n - 1);
}

/* linear iterative process - number of iterations grows linearly with n
 * sumarized by a fixed number of state variables and fixed rules on how to
 * modify the variables to reach the next state
 */
std::size_t factorial_iterative(std::size_t const n) {
  std::size_t it = 2;     // iteration
  std::size_t result = 1; // result of factorial

  while (it <= n) {
    result = result * it;
    ++it;
  }

  return result;
}

#define FACTORIAL_RECvITER_N
#ifdef FACTORIAL_RECvITER_Y

int main() {
  println(factorial_recursive(5));
  println(factorial_iterative(5));
  return 0;
}

#endif

/*
 * an iterative process can be implemented on basic hardware - the state
 * variables give all the nessecary information. a recursive process requires
 * that the hardware has a stack - a mechanism to keep track of the implicit
 * state "where are we in the process of recursion"
 */

//***************** EXERCISE 1.10 ACKERMANN'S FUNCTION

double A(double x, double y) { // NOLINT
  if (y == 0) {
    return 0;
  }
  if (x == 0) {
    return 2 * y;
  }
  if (y == 1) {
    return 2;
  }
  return A(x - 1, A(x, y - 1));
}

#define ACKERMANNS_Y
#ifdef ACKERMANNS_Y

int main() { println(A(3, 4)); } // LOL

#endif
