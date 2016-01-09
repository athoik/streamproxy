#ifndef _stbtraits_h_
#define _stbtraits_h_

#include <stdint.h>
#include <stddef.h>

typedef enum
{
	stb_transcoding_unknown,
	stb_transcoding_vuplus,
	stb_transcoding_enigma,
} stb_transcoding_t;

typedef enum
{
	stb_traits_type_bool,
	stb_traits_type_int,
	stb_traits_type_string,
	stb_traits_type_string_enum,
} stb_feature_type_t;

typedef struct
{
	const char *file;
	const char *content;
} stb_id_t;

typedef struct
{
	stb_feature_type_t	type;
	const char 			*description;
	const char			*id;
	bool				settable;
	const char			*api_data;

	union
	{
		struct
		{
			bool default_value;
		} bool_type;

		struct
		{
			int default_value;
			int min_value;
			int max_value;
			int scaling_factor;
		} int_type;

		struct
		{
			const char *default_value;
			size_t min_length;
			size_t max_length;
		} string_type;

		struct
		{
			const char *default_value;
			const char *enum_values[16];
		} string_enum_type;
	} value;
} stb_feature_t;

typedef struct
{
	const char				*manufacturer;
	const char 				*model;
	const char				*chipset;
	stb_transcoding_t		transcoding_type;
	int						encoders;
	size_t					num_id;
	const stb_id_t			id[2];
	size_t					num_features;
	const stb_feature_t		*features;
	size_t				extend_pid;
} stb_traits_t;

typedef struct
{
	size_t					num_traits;
	const stb_traits_t		traits_entry[7];
} stbs_traits_t;

extern const stbs_traits_t stbs_traits;

#endif
