{
  'includes': [
    'common.gypi',
  ],
  'targets': [
    {
      'target_name': 'combinator',
      'product_name': 'SenriganCombinator',
      'type': 'executable',
      'include_dirs': [
        '../combinator',
      ],
      'sources':
      [
        '../combinator/cell.cpp',
        '../combinator/combinator.cpp',
        '../combinator/crawler.cpp',
        '../combinator/image.cpp',
        '../combinator/imageprocessor.cpp',
        '../combinator/main.cpp',
        '../combinator/mysqldatabase.cpp',
        '../combinator/mysqlresultset.cpp',
      ],
      'link_settings': {
        'libraries': [
          '-lmysqlcppconn',
          '-lyaml-cpp',
          '-lglog'
        ],
      }
    }
  ]
}
