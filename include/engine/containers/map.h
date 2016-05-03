// map.h
//
// The map is a resizable container that maps a key to a value which
// automatically grows and shrinks as items are added or removed respectively.
//
// This is implemented using a hash function and a set of bins that determine
// the location of the item.
//
#ifndef NGE_CNTR_MAP_H
#define NGE_CNTR_MAP_H

#include <functional>
#include <engine/utility/hasher.h>

#include "engine/containers/dynamic_array.h"

namespace nge
{

namespace cntr
{

// TODO: consider using progressive bin copy afte resize if necessary
// TODO: cache hashes in separate array if necessary
template <typename K, typename V>
class Map
{
  public:
    // STRUCTURES
    /**
     * Defines a key-value pair.
     */
    struct Pair;

  private:
    // CONSTANTS
    /**
     * The minimum number of bins.
     */
    static constexpr uint32 MIN_BINS = 32;

    /**
     * Defines a bin that is empty and does not hold a value.
     */
    static constexpr uint32 BIN_EMPTY = static_cast<uint32>( -1 );

    /**
     * The threshold percentage at which the map grows.
     */
    static constexpr uint32 GROW_THRESHOLD = 70;

    /**
     * The threshold percentage at which the map shrinks.
     */
    static constexpr uint32 SHRINK_THRESHOLD = 30;

    // MEMBERS
    /**
     * The bin allocator.
     */
    mem::AllocatorGuard<uint32> _binAlloc;

    /**
     * The key-value pairs.
     */
    DynamicArray<Pair> _pairs;

    /**
     * The hash function.
     */
    std::function<uint32( const K& )> _hashFunc;

    /**
     * The bins.
     */
    uint32* _bins;

    /**
     * The number of bins in use.
     */
    uint32 _binsInUse;

    /**
     * The total number of bins.
     */
    uint32 _binCount;

    // HELPER FUNCTIONS
    /**
     * Creates a new pair.
     */
    Pair makePair( const K& key, const V& value ) const;

    /**
     * Creates a new pair.
     */
    Pair makePair( const K& key, V&& value ) const;

    /**
     * Gets the index of a bin that should hold the given key.
     *
     * The returned index may already have a mapping and needs to be
     * checked that it is empty.
     */
    uint32 findBinForKey( const K& key ) const;

    /**
     * Computes the hash for the given key.
     */
    uint32 hash( const K& key ) const;

    /**
     * Probes for the next position.
     */
    uint32 probe( uint32 probes ) const;

    /**
     * Wraps the bin index to be within the bounds.
     */
    uint32 wrap( uint32 index ) const;

    /**
     * Checks if the bin at the given index is empty.
     *
     * Behavior is undefined when:
     * binIndex is invalid.
     */
    bool isBinEmpty( uint32 binIndex ) const;

    /**
     * Checks if the bin at the given indx contains the given key.
     *
     * This will return false if binIndex is invalid.
     */
    bool doesBinContain( uint32 binIndex, const K& key ) const;

    /**
     * Checks if the bin array should shrink.
     */
    bool shouldShrink() const;

    /**
     * Checks if the bin array should grow.
     */
    bool shouldGrow() const;

    /**
     * Grows the bin array to twice the current capacity.
     */
    void grow();

    /**
     * Shrinks the bin array to half the current capacity.
     */
    void shrink();

    /**
     * Resizes the bin array to the specified size.
     */
    void resize( uint32 newSize );

    /**
     * Clears all of the bins.
     */
    void clearBins();

  public:
    // CLASSES
    /**
     * Iterates through the key set.
     */
    class ConstKeyIterator
    {
      private:
        // MEMBERS
        /**
         * The set of values that are being iterated.
         */
        const DynamicArray<Pair>* _iterValues;

        /**
         * The current position in the set.
         */
        uint32 _iterIndex;

      public:
        // CONSTRUCTORS
        /**
         * Constructs a new iterator.
         */
        ConstKeyIterator();

        /**
         * Constructs an iterator for the map with the given index.
         */
        ConstKeyIterator( const Map<K, V>* map, uint32 index );

        /**
         * Constructs a copy of the given iterator.
         */
        ConstKeyIterator( const ConstKeyIterator& iter );

        /**
         * Destructs the iterator.
         */
        ~ConstKeyIterator();

        // OPERATORS
        /**
         * Assigns this as a copy of the other iterator.
         */
        ConstKeyIterator& operator=( const ConstKeyIterator& iter );

        /**
         * Moves to the next item.
         */
        ConstKeyIterator& operator++();

        /**
         * Moves to the next item.
         */
        ConstKeyIterator& operator++( int32 );

        /**
         * Moves to the previous item.
         */
        ConstKeyIterator& operator--();

        /**
         * Moves to the previous item.
         */
        ConstKeyIterator& operator--( int32 );

        /**
         * Gets the element at the current position.
         */
        const K& operator*() const;

        /**
         * Gets the element at the current position.
         *
         * The value must not be modified in a way that it's hash code would
         * change. To do so will cause undefined behavior.
         */
        const K* operator->() const;

        /**
         * Checks if the other iterator is at the same position.
         */
        bool operator==( const ConstKeyIterator& iter ) const;

        /**
         * Checks if the other iterator is not at the same position.
         */
        bool operator!=( const ConstKeyIterator& iter ) const;
    };

    /**
     * Iterates through the value set.
     */
    class ConstValueIterator
    {
      private:
        // MEMBERS
        /**
         * The set of values that are being iterated.
         */
        const DynamicArray<Pair>* _iterValues;

        /**
         * The current position in the set.
         */
        uint32 _iterIndex;

      public:
        // CONSTRUCTORS
        /**
         * Constructs a new iterator.
         */
        ConstValueIterator();

        /**
         * Constructs an iterator for the map with the given index.
         */
        ConstValueIterator( const Map<K, V>* map, uint32 index );

        /**
         * Constructs a copy of the given iterator.
         */
        ConstValueIterator( const ConstValueIterator& iter );

        /**
         * Destructs the iterator.
         */
        ~ConstValueIterator();

        // OPERATORS
        /**
         * Assigns this as a copy of the other iterator.
         */
        ConstValueIterator& operator=( const ConstValueIterator& iter );

        /**
         * Moves to the next item.
         */
        ConstValueIterator& operator++();

        /**
         * Moves to the next item.
         */
        ConstValueIterator& operator++( int32 );

        /**
         * Moves to the previous item.
         */
        ConstValueIterator& operator--();

        /**
         * Moves to the previous item.
         */
        ConstValueIterator& operator--( int32 );

        /**
         * Gets the element at the current position.
         */
        const V& operator*() const;

        /**
         * Gets the element at the current position.
         *
         * The value must not be modified in a way that it's hash code would
         * change. To do so will cause undefined behavior.
         */
        const V* operator->() const;

        /**
         * Checks if the other iterator is at the same position.
         */
        bool operator==( const ConstValueIterator& iter ) const;

        /**
         * Checks if the other iterator is not at the same position.
         */
        bool operator!=( const ConstValueIterator& iter ) const;
    };

    // STRUCTURES
    struct Pair
    {
        K key;
        V value;
    };

    // CONSTRUCTORS
    /**
     * Constructs a new map.
     */
    Map();

    /**
     * Constructs a new map with the given initial capacity.
     */
    Map( uint32 capacity );

    /**
     * Constructs a new set that uses the given hash function.
     */
    Map( const std::function<uint32( const K& )>& hashFunc );

    /**
     * Constructs a new map with the given initial capacity that uses
     * the given hash function.
     */
    Map( uint32 capacity, const std::function<uint32( const K& )>& hashFunc );

    /**
     * Constructs a new map that uses the given allocators.
     */
    Map( mem::IAllocator<Pair>* pairAlloc, mem::IAllocator<uint32>* intAlloc );

    /**
     * Constructs a new map using the given allocators and initial capacity.
     */
    Map( mem::IAllocator<Pair>* pairAlloc, mem::IAllocator<uint32>* intAlloc,
        uint32 capacity );

    /**
     * Constructs a new map using the given allocators and hash function.
     */
    Map( mem::IAllocator<Pair>* pairAlloc, mem::IAllocator<uint32>* intAlloc,
        const std::function<uint32( const K& )>& hashFunc );

    /**
     * Constructs a new map using the given allocators, initial capacity, and
     * hash function.
     */
    Map( mem::IAllocator<Pair>* pairAlloc, mem::IAllocator<uint32>* intAlloc,
        uint32 capacity, const std::function<uint32( const K& )>& hashFunc );

    /**
     * Constructs a copy of the given map.
     */
    Map( const Map<K, V>& map );

    /**
     * Moves the map to a new instance.
     */
    Map( Map<K, V>&& map );

    /**
     * Destructs the map.
     */
    ~Map();

    // OPERATORS
    /**
     * Assigns this as a copy of the given map.
     */
    Map<K, V>& operator=( const Map<K, V>& map );

    /**
     * Moves the map data to this instance.
     */
    Map<K, V>& operator=( Map<K, V>&& map );

    /**
     * Gets the value that is associated with the given key.
     *
     * Behavior is undefined when:
     * There is no mapping for the key.
     */
    const V& operator[]( const K& key ) const;

    /**
     * Gets the value that is associated with the given key.
     *
     * If a mapping does not exist it will be created.
     */
    V& operator[]( const K& key );

    // MEMBER FUNCTIONS
    /**
     * Puts the specified mapping into the map.
     */
    void put( const K& key, const V& value );

    /**
     * Puts the specified mapping into the map using the move operation.
     */
    void put( const K& key, V&& value );

    /**
     * Removes the mapping for the specified key.
     */
    void remove( const K& key );

    /**
     * Checks if the map contains a mapping for the given key.
     */
    bool has( const K& key ) const;

    /**
     * Removes all mappings.
     */
    void clear();

    /**
     * Gets an iterator for the mapped values.
     */
    ConstValueIterator cbegin() const;

    /**
     * Gets an iterator for the mapped values at the end of the list.
     */
    ConstValueIterator cend() const;

    /**
     * Gets an iterator for the key set.
     */
    ConstKeyIterator cKeysBegin() const;

    /**
     * Gets an iterator for the key set at the end.
     */
    ConstKeyIterator cKeysEnd() const;

    /**
     * Gets the number of key-value pairs in the map.
     */
    uint32 size() const;

    /**
     * Checks if the map is empty.
     */
    bool isEmpty() const;
};

// CONSTANTS
template <typename K, typename V>
constexpr uint32 Map<K, V>::MIN_BINS;

template <typename K, typename V>
constexpr uint32 Map<K, V>::BIN_EMPTY;

template <typename K, typename V>
constexpr uint32 Map<K, V>::GROW_THRESHOLD;

template <typename K, typename V>
constexpr uint32 Map<K, V>::SHRINK_THRESHOLD;

// CONSTRUCTORS
template <typename K, typename V>
inline
Map<K, V>::Map() : _binAlloc(), _pairs(), _hashFunc( &util::Hasher<K>::hash ),
                   _bins( nullptr ), _binsInUse( 0 ), _binCount( MIN_BINS )
{
    _bins = _binAlloc.get( _binCount );
    clearBins();
}

template <typename K, typename V>
inline
Map<K, V>::Map( uint32 capacity )
    : _binAlloc(), _pairs( capacity ), _hashFunc( &util::Hasher<K>::hash ),
      _bins( nullptr ), _binsInUse( 0 ), _binCount( MIN_BINS )
{
    while ( _binCount < capacity )
    {
        _binCount <<= 1;
    }

    _bins = _binAlloc.get( _binCount );
    clearBins();
}

template <typename K, typename V>
inline
Map<K, V>::Map( const std::function<uint32( const K& )>& hashFunc )
    : _binAlloc(), _pairs(), _hashFunc( hashFunc ),
      _bins( nullptr ), _binsInUse( 0 ), _binCount( MIN_BINS )
{
    _bins = _binAlloc.get( _binCount );
    clearBins();
}

template <typename K, typename V>
inline
Map<K, V>::Map( uint32 capacity,
                const std::function<uint32( const K& )>& hashFunc )
    : _binAlloc(), _pairs( capacity ), _hashFunc( hashFunc ),
      _bins( nullptr ), _binsInUse( 0 ), _binCount( MIN_BINS )
{
    while ( _binCount < capacity )
    {
        _binCount <<= 1;
    }

    _bins = _binAlloc.get( _binCount );
    clearBins();
}

template <typename K, typename V>
inline
Map<K, V>::Map( mem::IAllocator<Pair>* pairAlloc,
                mem::IAllocator<uint32>* intAlloc )
    : _binAlloc( intAlloc ), _pairs( pairAlloc ),
      _hashFunc( &util::Hasher<K>::hash ), _bins( nullptr ), _binsInUse( 0 ),
      _binCount( MIN_BINS )
{
    _bins = _binAlloc.get( _binCount );
    clearBins();
}

template <typename K, typename V>
inline
Map<K, V>::Map( mem::IAllocator<Pair>* pairAlloc,
                mem::IAllocator<uint32>* intAlloc, uint32 capacity )
    : _binAlloc( intAlloc ), _pairs( pairAlloc, capacity ),
      _hashFunc( &util::Hasher<K>::hash ), _bins( nullptr ), _binsInUse( 0 ),
      _binCount( MIN_BINS )
{
    while ( _binCount < capacity )
    {
        _binCount <<= 1;
    }

    _bins = _binAlloc.get( _binCount );
    clearBins();
}

template <typename K, typename V>
inline
Map<K, V>::Map( mem::IAllocator<Pair>* pairAlloc,
                mem::IAllocator<uint32>* intAlloc,
                const std::function<uint32( const K& )>& hashFunc )
    : _binAlloc( intAlloc ), _pairs( pairAlloc ), _hashFunc( hashFunc ),
      _bins( nullptr ), _binsInUse( 0 ), _binCount( MIN_BINS )
{
    _bins = _binAlloc.get( _binCount );
    clearBins();
}

template <typename K, typename V>
inline
Map<K, V>::Map( mem::IAllocator<Pair>* pairAlloc,
                mem::IAllocator<uint32>* intAlloc, uint32 capacity,
                const std::function<uint32( const K& )>& hashFunc )
    : _binAlloc( intAlloc ), _pairs( pairAlloc, capacity ),
      _hashFunc( hashFunc ), _bins( nullptr ), _binsInUse( 0 ),
      _binCount( MIN_BINS )
{
    while ( _binCount < capacity )
    {
        _binCount <<= 1;
    }

    _bins = _binAlloc.get( _binCount );
    clearBins();
}

template <typename K, typename V>
inline
Map<K, V>::Map( const Map<K, V>& map )
    : _binAlloc( map._binAlloc ), _pairs( map._pairs ),
      _hashFunc( map._hashFunc ), _bins( nullptr ),
      _binsInUse( map._binsInUse ), _binCount( map._binCount )
{
    _bins = _binAlloc.get( _binCount );
    mem::MemoryUtils::copy( _bins, map._bins, _binCount );
}

template <typename K, typename V>
inline
Map<K, V>::Map( Map<K, V>&& map )
    : _binAlloc( std::move( map._binAlloc ) ),
      _pairs( std::move( map._pairs ) ),
      _hashFunc( std::move( map._hashFunc ) ), _bins( map._bins ),
      _binsInUse( map._binsInUse ), _binCount( map._binCount )
{
    map._bins = nullptr;
    map._binsInUse = 0;
    map._binCount = 0;
}

template <typename K, typename V>
inline
Map<K, V>::~Map()
{
    if ( _bins != nullptr )
    {
        _binAlloc.release( _bins, _binCount );
        _bins = nullptr;
    }
    _binsInUse = 0;
    _binCount = 0;
}

// OPERATORS
template <typename K, typename V>
Map<K, V>& Map<K, V>::operator=( const Map<K, V>& map )
{
    if ( _bins != nullptr )
    {
        _binAlloc.release( _bins, _binCount );
    }

    _binAlloc = map._binAlloc;
    _pairs = map._pairs;
    _hashFunc = map._hashFunc;
    _binCount = map._binCount;
    _binsInUse = map._binsInUse;
    _bins = _binAlloc.get( _binCount );
    mem::MemoryUtils::copy( _bins, map._bins, _binCount );

    return *this;
}

template <typename K, typename V>
Map<K, V>& Map<K, V>::operator=( Map<K, V>&& map )
{
    if ( _bins != nullptr )
    {
        _binAlloc.release( _bins, _binCount );
    }

    _binAlloc = std::move( map._binAlloc );
    _pairs = std::move( map._pairs );
    _hashFunc = std::move( map._hashFunc );
    _bins = map._bins;
    _binCount = map._binCount;
    _binsInUse = map._binsInUse;

    map._bins = nullptr;
    map._binCount = 0;
    map._binsInUse = 0;

    return *this;
}

template <typename K, typename V>
inline
const V& Map<K, V>::operator[]( const K& key ) const
{
    uint32 binIndex = findBinForKey( key );
    assert( !isBinEmpty( binIndex ) );
    return _pairs[_bins[binIndex]].value;
}

template <typename K, typename V>
V& Map<K, V>::operator[]( const K& key )
{
    if ( shouldGrow() )
    {
        grow();
    }

    uint32 binIndex = findBinForKey( key );

    if ( isBinEmpty( binIndex ) )
    {
        ++_binsInUse;
        _bins[binIndex] = _pairs.size();

        V value;
        _pairs.push( makePair( key, value ) );
    }

    return _pairs[_bins[binIndex]].value;
}

// MEMBER FUNCTIONS
template <typename K, typename V>
void Map<K, V>::put( const K& key, const V& value )
{
    uint32 binIndex = findBinForKey( key );

    if ( isBinEmpty( binIndex ) )
    {
        ++_binsInUse;
        _bins[binIndex] = _pairs.size();
        _pairs.push( makePair( key, value ) );
    }
    else
    {
        _pairs[_bins[binIndex]] = makePair( key, value );
    }
}

template <typename K, typename V>
void Map<K, V>::put( const K& key, V&& value )
{
    uint32 binIndex = findBinForKey( key );

    if ( isBinEmpty( binIndex ) )
    {
        ++_binsInUse;
        _bins[binIndex] = _pairs.size();
        _pairs.push( makePair( key, std::move( value ) ) );
    }
    else
    {
        _pairs[_bins[binIndex]] = makePair( key, std::move( value ) );
    }
}

template <typename K, typename V>
void Map<K, V>::remove( const K& key )
{
    if ( shouldShrink() )
    {
        shrink();
    }

    uint32 binIndex = findBinForKey( key );
    uint32 i;
    if ( !isBinEmpty( binIndex ) )
    {
        --_binsInUse;
        _pairs.removeAt( _bins[binIndex] );

        // correct bin indices
        for ( i = 0; i < _binCount; ++i )
        {
            if ( !isBinEmpty( i ) && _bins[i] > _bins[binIndex] )
            {
                --( _bins[i] );
            }
        }

        _bins[binIndex] = BIN_EMPTY;
    }
}

template <typename K, typename V>
inline
bool Map<K, V>::has( const K& key ) const
{
    return !isBinEmpty( findBinForKey( key ) );
}

template <typename K, typename V>
inline
void Map<K, V>::clear()
{
    clearBins();
    _pairs.clear();
    _binsInUse = 0;
}

template <typename K, typename V>
inline
typename Map<K, V>::ConstValueIterator Map<K, V>::cbegin() const
{
    return ConstValueIterator( this, 0 );
}

template <typename K, typename V>
inline
typename Map<K, V>::ConstValueIterator Map<K, V>::cend() const
{
    return ConstValueIterator( this, _pairs.size() );
}

template <typename K, typename V>
inline
typename Map<K, V>::ConstKeyIterator Map<K, V>::cKeysBegin() const
{
    return ConstKeyIterator( this, 0 );
}

template <typename K, typename V>
inline
typename Map<K, V>::ConstKeyIterator Map<K, V>::cKeysEnd() const
{
    return ConstKeyIterator( this, _pairs.size() );
}

template <typename K, typename V>
inline
uint32 Map<K, V>::size() const
{
    return _pairs.size();
}

template <typename K, typename V>
inline
bool Map<K, V>::isEmpty() const
{
    return _pairs.isEmpty();
}

// HELPER FUNCTIONS
template <typename K, typename V>
inline
typename Map<K, V>::Pair
Map<K, V>::makePair( const K& key, const V& value ) const
{
    Pair pair;
    pair.key = key;
    pair.value = value;
    return pair;
}

template <typename K, typename V>
inline
typename Map<K, V>::Pair
Map<K, V>::makePair( const K& key, V&& value ) const
{
    Pair pair;
    pair.key = key;
    pair.value = std::move( value );
    return pair;
}

template <typename K, typename V>
inline
uint32 Map<K, V>::findBinForKey( const K& key ) const
{
    const uint32 hashCode = hash( key );
    uint32 i;
    uint32 probes;
    for ( i = wrap( hashCode ), probes = 0;
          !isBinEmpty( i ) && !doesBinContain( i, key );
          i = probe( ++probes ) )
    {
        // do nothing
    }

    return i;
}

template <typename K, typename V>
inline
uint32 Map<K, V>::hash( const K& key ) const
{
    return _hashFunc( key );
}

template <typename K, typename V>
inline
uint32 Map<K, V>::probe( uint32 probes ) const
{
    return probes;
}

template <typename K, typename V>
inline
uint32 Map<K, V>::wrap( uint32 index ) const
{
    return index & ( _binCount - 1 );
}

template <typename K, typename V>
inline
bool Map<K, V>::isBinEmpty( uint32 binIndex ) const
{
    assert( binIndex < _binCount );
    return _bins[binIndex] == BIN_EMPTY;
}

template <typename K, typename V>
inline
bool Map<K, V>::doesBinContain( uint32 binIndex, const K& key ) const
{
    return binIndex < _binCount && !isBinEmpty( binIndex ) &&
       _pairs[_bins[binIndex]].key == key;
}

template <typename K, typename V>
inline
bool Map<K, V>::shouldShrink() const
{
    return ( ( _binsInUse * 100 ) / _binCount ) <= SHRINK_THRESHOLD &&
           _binCount > MIN_BINS;
}

template <typename K, typename V>
inline
bool Map<K, V>::shouldGrow() const
{
    return ( ( _binsInUse * 100 ) / _binCount ) >= GROW_THRESHOLD;
}

template <typename K, typename V>
inline
void Map<K, V>::grow()
{
    resize( _binCount << 1 );
}

template <typename K, typename V>
inline
void Map<K, V>::shrink()
{
    resize( _binCount >> 1 );
}

template <typename K, typename V>
void Map<K, V>::resize( uint32 newSize )
{
    assert( _bins != nullptr );
    _binAlloc.release( _bins, _binCount );
    _bins = _binAlloc.get( newSize );
    _binCount = newSize;
    clearBins();

    uint32 i;
    uint32 pos;
    for ( i = 0; i < _pairs.size(); ++i )
    {
        pos = findBinForKey( _pairs[i].key );
        _bins[pos] = i;
    }
}

template <typename K, typename V>
inline
void Map<K, V>::clearBins()
{
    mem::MemoryUtils::set( _bins, BIN_EMPTY, _binCount );
}

// KEY ITERATOR CONSTRUCTORS
template <typename K, typename V>
inline
Map<K, V>::ConstKeyIterator::ConstKeyIterator()
    : _iterValues( nullptr ), _iterIndex( 0 )
{
}

template <typename K, typename V>
inline
Map<K, V>::ConstKeyIterator::ConstKeyIterator( const Map<K, V>* map,
                                               uint32 index )
    : _iterValues( &( map->_pairs ) ), _iterIndex( index )
{
}

template <typename K, typename V>
inline
Map<K, V>::ConstKeyIterator::ConstKeyIterator( const ConstKeyIterator& iter )
    : _iterValues( iter._iterValues ), _iterIndex( iter._iterIndex )
{
}

template <typename K, typename V>
inline
Map<K, V>::ConstKeyIterator::~ConstKeyIterator()
{
}

// KEY ITERATOR OPERATORS
template <typename K, typename V>
inline
typename Map<K, V>::ConstKeyIterator&
Map<K, V>::ConstKeyIterator::operator=( const ConstKeyIterator& iter )
{
    _iterValues = iter._iterValues;
    _iterIndex = iter._iterIndex;

    return *this;
}

template <typename K, typename V>
inline
typename Map<K, V>::ConstKeyIterator&
Map<K, V>::ConstKeyIterator::operator++()
{
    ++_iterIndex;
    return *this;
}

template <typename K, typename V>
inline
typename Map<K, V>::ConstKeyIterator&
Map<K, V>::ConstKeyIterator::operator++( int32 )
{
    ++_iterIndex;
    return *this;
}

template <typename K, typename V>
inline
typename Map<K, V>::ConstKeyIterator&
Map<K, V>::ConstKeyIterator::operator--()
{
    --_iterIndex;
    return *this;
}

template <typename K, typename V>
inline
typename Map<K, V>::ConstKeyIterator&
Map<K, V>::ConstKeyIterator::operator--( int32 )
{
    --_iterIndex;
    return *this;
}

template <typename K, typename V>
inline
const K& Map<K, V>::ConstKeyIterator::operator*() const
{
    return ( *_iterValues )[_iterIndex].key;
}

template <typename K, typename V>
inline
const K* Map<K, V>::ConstKeyIterator::operator->() const
{
    return &( *_iterValues )[_iterIndex].key;
}

template <typename K, typename V>
inline
bool Map<K, V>::ConstKeyIterator::operator==(
    const ConstKeyIterator& iter ) const
{
    return _iterValues == iter._iterValues && _iterIndex == iter._iterIndex;
}

template <typename K, typename V>
inline
bool Map<K, V>::ConstKeyIterator::operator!=(
    const ConstKeyIterator& iter ) const
{
    return _iterValues != iter._iterValues || _iterIndex != iter._iterIndex;
}

// VALUE ITERATOR CONSTRUCTORS
template <typename K, typename V>
inline
Map<K, V>::ConstValueIterator::ConstValueIterator()
    : _iterValues( nullptr ), _iterIndex( 0 )
{
}

template <typename K, typename V>
inline
Map<K, V>::ConstValueIterator::ConstValueIterator( const Map<K, V>* map,
                                                   uint32 index )
    : _iterValues( &( map->_pairs ) ), _iterIndex( index )
{
}

template <typename K, typename V>
inline
Map<K, V>::ConstValueIterator::ConstValueIterator(
    const ConstValueIterator& iter )
    : _iterValues( iter._iterValues ), _iterIndex( iter._iterIndex )
{
}

template <typename K, typename V>
inline
Map<K, V>::ConstValueIterator::~ConstValueIterator()
{
}

// VALUE ITERATOR OPERATORS
template <typename K, typename V>
inline
typename Map<K, V>::ConstValueIterator&
Map<K, V>::ConstValueIterator::operator=( const ConstValueIterator& iter )
{
    _iterValues = iter._iterValues;
    _iterIndex = iter._iterIndex;

    return *this;
}

template <typename K, typename V>
inline
typename Map<K, V>::ConstValueIterator&
Map<K, V>::ConstValueIterator::operator++()
{
    ++_iterIndex;
    return *this;
}

template <typename K, typename V>
inline
typename Map<K, V>::ConstValueIterator&
Map<K, V>::ConstValueIterator::operator++( int32 )
{
    ++_iterIndex;
    return *this;
}

template <typename K, typename V>
inline
typename Map<K, V>::ConstValueIterator&
Map<K, V>::ConstValueIterator::operator--()
{
    --_iterIndex;
    return *this;
}

template <typename K, typename V>
inline
typename Map<K, V>::ConstValueIterator&
Map<K, V>::ConstValueIterator::operator--( int32 )
{
    --_iterIndex;
    return *this;
}

template <typename K, typename V>
inline
const V& Map<K, V>::ConstValueIterator::operator*() const
{
    return ( *_iterValues )[_iterIndex].value;
}

template <typename K, typename V>
inline
const V* Map<K, V>::ConstValueIterator::operator->() const
{
    return &( *_iterValues )[_iterIndex].value;
}

template <typename K, typename V>
inline
bool Map<K, V>::ConstValueIterator::operator==(
    const ConstValueIterator& iter ) const
{
    return _iterValues == iter._iterValues && _iterIndex == iter._iterIndex;
}

template <typename K, typename V>
inline
bool Map<K, V>::ConstValueIterator::operator!=(
    const ConstValueIterator& iter ) const
{
    return _iterValues != iter._iterValues || _iterIndex != iter._iterIndex;
}

} // End nspc cntr

} // End nspc nge

#endif // NGE_CNTR_MAP_H
