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
        '../combinator/combinator.cpp',
        '../combinator/crawler.cpp',
        '../combinator/main.cpp',
        '../combinator/mysqldatabase.cpp',
        '../combinator/mysqlresultset.cpp',
        '../combinator/processor.cpp',
      ],
      'link_settings': {
        'libraries': [
          '-lmysqlcppconn'
        ],
      }
    }
  ]
}
