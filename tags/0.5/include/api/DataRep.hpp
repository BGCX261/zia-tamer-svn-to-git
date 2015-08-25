#ifndef _ZIA_API_DATAREP_H_
#define _ZIA_API_DATAREP_H_

#include <iostream>
#include <string>
#include <map>
#include <list>

#include "defines.hpp"

_BOF_ZIA_API_

/*!
 * \brief Data representation.
 *
 * Useful for conf or data storage.
 *
 * Data can represents:
 * - key => value
 * - key => list of value
 *
 * ( Easy implementation with JSon files )
 *
 * Example of Keys:
 * - \c myvar.toto
 * - \c myvar.mysubvar.CaseSensitiv
 *
 * <h2> Zia core implementations: </h2>
 * \code

//
// DataRep implementation:
//
DataRep::DataRep();
DataRep::~DataRep();
bool                            DataRep::hasValue(const std::string& key) const;
bool                            DataRep::hasList(const std::string& key) const;
const std::string&              DataRep::value(const std::string& key) const;
void                            DataRep::value(const std::string& key,
                                               const std::string& value);
std::list< std::string >&       DataRep::list(const std::string& key);
const std::list< std::string >& DataRep::const_list(const std::string& key) const;
void                            DataRep::clear();
const std::map< std::string, std::string >&                 DataRep::getValues() const;
const std::map< std::string, std::list< std::string > >&    DataRep::getLists() const;


 * \endcode
 */
class DataRep
{
public:
    /*!
     * \brief Constructor.
     *
     * Empty DataRep
     */
    DataRep();

    /*!
     * \brief Destructor.
     */
    virtual ~DataRep();

    /*!
     * \brief Check if it has the \a key.
     *
     * An empty value is considered as non-existent.
     *
     * \return true if \a key exists.
     */
    bool                        hasValue(const std::string& key) const;

    /*!
     * \brief Check if it has the \a key.
     *
     * An empty list is considered as non-existent.
     *
     * \return true if \a key exists.
     */
    bool                        hasList(const std::string& key) const;

    /*!
     * \brief Get a value
     *
     * \return The value if \a key exists,
     * an empty string if \a key doesnot exist.
     */
    const std::string&          value(const std::string& key) const;

    /*!
     * \brief Set a value
     *
     */
    void                        value(const std::string& key,
                                      const std::string& value);

    /*!
     * \brief Get reference on a list.
     *
     * If \a key doesnot exist, the \a key is create with
     * an empty list.
     *
     * \return The list.
     */
    std::list< std::string >&   list(const std::string& key);

    /*!
     * \brief Get a const reference on a list.
     *
     * \return The list, an empty list if \a key does not exist.
     */
    const std::list< std::string >& const_list(const std::string& key) const;

    /*!
     * \brief Remove all datas
     */
    void                        clear();

    /*!
     * \brief Print datas.
     *
     * \param out Where datas will be print.
     */
    void                        print(std::ostream& out) const;

    /*!
     * \brief mValues getter.
     */
    const std::map< std::string, std::string >&                 getValues() const;

    /*!
     * \brief mLists getter.
     */
    const std::map< std::string, std::list< std::string > >&    getLists() const;

protected:
    /*!
     * \brief Key/Value datas
     */
    std::map< std::string, std::string >
    mValues;

    /*!
     * \brief Key/List datas
     */
    std::map< std::string, std::list< std::string > >
    mLists;

};

_EOF_ZIA_API_

#endif /* _ZIA_API_DATAREP_H_ */
