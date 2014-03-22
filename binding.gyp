{
  'targets':
  [
    {
      'target_name': 'baseJump',
      'sources': [ 
        'cc/baseJump.cc',
        'cc/BigInteger.cc',
        'cc/BigIntegerAlgorithms.cc',
        'cc/BigIntegerUtils.cc',
        'cc/BigUnsigned.cc',
        'cc/BigUnsignedInABase.cc'
      ],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'conditions': [
        ['OS=="mac"', {
          'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
          }
        }]
      ]
    }
  ]
}