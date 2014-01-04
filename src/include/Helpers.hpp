#ifndef HELPERS_HPP
#define HELPERS_HPP

template <class T>
T max(const T& a, const T& b){
  /**
   * @brief Calcule le maximum entre deux éléments.
   * @details Aucune vérification sur la présence de l'opérateur < n'est faite.
   * @param a 1er élément à tester
   * @param b 1er élément à tester
   * @return @a a si @e a>b, @a b sinon
   */
  return (a>b)?a:b;
}

template <class T>
T min(const T& a, const T& b){
    /**
   * @brief Calcule le minimum entre deux éléments.
   * @details Aucune vérification sur la présence de l'opérateur > n'est faite.
   * @param a 1er élément à tester
   * @param b 1er élément à tester
   * @return @a b si @e a>b, @a a sinon
   */
    return (a>b)?b:a;
}

#endif
