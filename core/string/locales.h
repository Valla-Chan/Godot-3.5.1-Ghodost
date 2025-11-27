/**************************************************************************/
/*  locales.h                                                             */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#ifndef LOCALES_H
#define LOCALES_H

// ISO 639-1 language codes (and a couple of three-letter ISO 639-2 codes),
// with the addition of glibc locales with their regional identifiers.
// This list must match the language names (in English) of locale_names.
//
// References:
// - https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes
// - https://lh.2xlibre.net/locales/
// - https://iso639-3.sil.org/

static const char *locale_list[] = {
	"aa", //  Afar
	"aa_DJ", //  Afar (Djibouti)
	"aa_ER", //  Afar (Eritrea)
	"aa_ET", //  Afar (Ethiopia)
	"af", //  Afrikaans
	"af_ZA", //  Afrikaans (South Africa)
	"agr_PE", //  Aguaruna (Peru)
	"ak_GH", //  Akan (Ghana)
	"am_ET", //  Amharic (Ethiopia)
	"an_ES", //  Aragonese (Spain)
	"anp_IN", //  Angika (India)
	"ar", //  Arabic
	"ar_AE", //  Arabic (United Arab Emirates)
	"ar_BH", //  Arabic (Bahrain)
	"ar_DZ", //  Arabic (Algeria)
	"ar_EG", //  Arabic (Egypt)
	"ar_IN", //  Arabic (India)
	"ar_IQ", //  Arabic (Iraq)
	"ar_JO", //  Arabic (Jordan)
	"ar_KW", //  Arabic (Kuwait)
	"ar_LB", //  Arabic (Lebanon)
	"ar_LY", //  Arabic (Libya)
	"ar_MA", //  Arabic (Morocco)
	"ar_OM", //  Arabic (Oman)
	"ar_QA", //  Arabic (Qatar)
	"ar_SA", //  Arabic (Saudi Arabia)
	"ar_SD", //  Arabic (Sudan)
	"ar_SS", //  Arabic (South Soudan)
	"ar_SY", //  Arabic (Syria)
	"ar_TN", //  Arabic (Tunisia)
	"ar_YE", //  Arabic (Yemen)
	"as_IN", //  Assamese (India)
	"ast_ES", //  Asturian (Spain)
	"ayc_PE", //  Southern Aymara (Peru)
	"ay_PE", //  Aymara (Peru)
	"az", //  Azerbaijani
	"az_AZ", //  Azerbaijani (Azerbaijan)
	"be", //  Belarusian
	"be_BY", //  Belarusian (Belarus)
	"bem_ZM", //  Bemba (Zambia)
	"ber_DZ", //  Berber languages (Algeria)
	"ber_MA", //  Berber languages (Morocco)
	"bg", //  Bulgarian
	"bg_BG", //  Bulgarian (Bulgaria)
	"bhb_IN", //  Bhili (India)
	"bho_IN", //  Bhojpuri (India)
	"bi_TV", //  Bislama (Tuvalu)
	"bn", //  Bengali
	"bn_BD", //  Bengali (Bangladesh)
	"bn_IN", //  Bengali (India)
	"bo", //  Tibetan
	"bo_CN", //  Tibetan (China)
	"bo_IN", //  Tibetan (India)
	"br", //  Breton
	"br_FR", //  Breton (France)
	"brx_IN", //  Bodo (India)
	"bs_BA", //  Bosnian (Bosnia and Herzegovina)
	"byn_ER", //  Bilin (Eritrea)
	"ca", //  Catalan
	"ca_AD", //  Catalan (Andorra)
	"ca_ES", //  Catalan (Spain)
	"ca_FR", //  Catalan (France)
	"ca_IT", //  Catalan (Italy)
	"ce_RU", //  Chechen (Russia)
	"chr_US", //  Cherokee (United States)
	"cmn_TW", //  Mandarin Chinese (Taiwan)
	"crh_UA", //  Crimean Tatar (Ukraine)
	"csb_PL", //  Kashubian (Poland)
	"cs", //  Czech
	"cs_CZ", //  Czech (Czech Republic)
	"cv_RU", //  Chuvash (Russia)
	"cy_GB", //  Welsh (United Kingdom)
	"da", //  Danish
	"da_DK", //  Danish (Denmark)
	"de", //  German
	"de_AT", //  German (Austria)
	"de_BE", //  German (Belgium)
	"de_CH", //  German (Switzerland)
	"de_DE", //  German (Germany)
	"de_IT", //  German (Italy)
	"de_LU", //  German (Luxembourg)
	"doi_IN", //  Dogri (India)
	"dv_MV", //  Dhivehi (Maldives)
	"dz_BT", //  Dzongkha (Bhutan)
	"el", //  Greek
	"el_CY", //  Greek (Cyprus)
	"el_GR", //  Greek (Greece)
	"en", //  English
	"en_AG", //  English (Antigua and Barbuda)
	"en_AU", //  English (Australia)
	"en_BW", //  English (Botswana)
	"en_CA", //  English (Canada)
	"en_DK", //  English (Denmark)
	"en_GB", //  English (United Kingdom)
	"en_HK", //  English (Hong Kong)
	"en_IE", //  English (Ireland)
	"en_IL", //  English (Israel)
	"en_IN", //  English (India)
	"en_NG", //  English (Nigeria)
	"en_NZ", //  English (New Zealand)
	"en_PH", //  English (Philippines)
	"en_SG", //  English (Singapore)
	"en_US", //  English (United States)
	"en_ZA", //  English (South Africa)
	"en_ZM", //  English (Zambia)
	"en_ZW", //  English (Zimbabwe)
	"eo", //  Esperanto
	"es", //  Spanish
	"es_AR", //  Spanish (Argentina)
	"es_BO", //  Spanish (Bolivia)
	"es_CL", //  Spanish (Chile)
	"es_CO", //  Spanish (Colombia)
	"es_CR", //  Spanish (Costa Rica)
	"es_CU", //  Spanish (Cuba)
	"es_DO", //  Spanish (Dominican Republic)
	"es_EC", //  Spanish (Ecuador)
	"es_ES", //  Spanish (Spain)
	"es_GT", //  Spanish (Guatemala)
	"es_HN", //  Spanish (Honduras)
	"es_MX", //  Spanish (Mexico)
	"es_NI", //  Spanish (Nicaragua)
	"es_PA", //  Spanish (Panama)
	"es_PE", //  Spanish (Peru)
	"es_PR", //  Spanish (Puerto Rico)
	"es_PY", //  Spanish (Paraguay)
	"es_SV", //  Spanish (El Salvador)
	"es_US", //  Spanish (United States)
	"es_UY", //  Spanish (Uruguay)
	"es_VE", //  Spanish (Venezuela)
	"et", //  Estonian
	"et_EE", //  Estonian (Estonia)
	"eu", //  Basque
	"eu_ES", //  Basque (Spain)
	"fa", //  Persian
	"fa_IR", //  Persian (Iran)
	"ff_SN", //  Fulah (Senegal)
	"fi", //  Finnish
	"fi_FI", //  Finnish (Finland)
	"fil", //  Filipino
	"fil_PH", //  Filipino (Philippines)
	"fo_FO", //  Faroese (Faroe Islands)
	"fr", //  French
	"fr_BE", //  French (Belgium)
	"fr_CA", //  French (Canada)
	"fr_CH", //  French (Switzerland)
	"fr_FR", //  French (France)
	"fr_LU", //  French (Luxembourg)
	"fur_IT", //  Friulian (Italy)
	"fy_DE", //  Western Frisian (Germany)
	"fy_NL", //  Western Frisian (Netherlands)
	"ga", //  Irish
	"ga_IE", //  Irish (Ireland)
	"gd_GB", //  Scottish Gaelic (United Kingdom)
	"gez_ER", //  Geez (Eritrea)
	"gez_ET", //  Geez (Ethiopia)
	"gl", //  Galician
	"gl_ES", //  Galician (Spain)
	"gu_IN", //  Gujarati (India)
	"gv_GB", //  Manx (United Kingdom)
	"hak_TW", //  Hakka Chinese (Taiwan)
	"ha_NG", //  Hausa (Nigeria)
	"he", //  Hebrew
	"he_IL", //  Hebrew (Israel)
	"hi", //  Hindi
	"hi_IN", //  Hindi (India)
	"hne_IN", //  Chhattisgarhi (India)
	"hr", //  Croatian
	"hr_HR", //  Croatian (Croatia)
	"hsb_DE", //  Upper Sorbian (Germany)
	"ht_HT", //  Haitian (Haiti)
	"hu", //  Hungarian
	"hu_HU", //  Hungarian (Hungary)
	"hus_MX", //  Huastec (Mexico)
	"hy_AM", //  Armenian (Armenia)
	"ia_FR", //  Interlingua (France)
	"id", //  Indonesian
	"id_ID", //  Indonesian (Indonesia)
	"ig_NG", //  Igbo (Nigeria)
	"ik_CA", //  Inupiaq (Canada)
	"is", //  Icelandic
	"is_IS", //  Icelandic (Iceland)
	"it", //  Italian
	"it_CH", //  Italian (Switzerland)
	"it_IT", //  Italian (Italy)
	"iu_CA", //  Inuktitut (Canada)
	"ja", //  Japanese
	"ja_JP", //  Japanese (Japan)
	"kab_DZ", //  Kabyle (Algeria)
	"ka", //  Georgian
	"ka_GE", //  Georgian (Georgia)
	"kk_KZ", //  Kazakh (Kazakhstan)
	"kl_GL", //  Kalaallisut (Greenland)
	"km", //  Central Khmer
	"km_KH", //  Central Khmer (Cambodia)
	"kn_IN", //  Kannada (India)
	"kok_IN", //  Konkani (India)
	"ko", //  Korean
	"ko_KR", //  Korean (South Korea)
	"ks_IN", //  Kashmiri (India)
	"ku", //  Kurdish
	"ku_TR", //  Kurdish (Turkey)
	"kw_GB", //  Cornish (United Kingdom)
	"ky_KG", //  Kirghiz (Kyrgyzstan)
	"lb_LU", //  Luxembourgish (Luxembourg)
	"lg_UG", //  Ganda (Uganda)
	"li_BE", //  Limburgan (Belgium)
	"li_NL", //  Limburgan (Netherlands)
	"lij_IT", //  Ligurian (Italy)
	"ln_CD", //  Lingala (Congo)
	"lo_LA", //  Lao (Laos)
	"lt", //  Lithuanian
	"lt_LT", //  Lithuanian (Lithuania)
	"lv", //  Latvian
	"lv_LV", //  Latvian (Latvia)
	"lzh_TW", //  Literary Chinese (Taiwan)
	"mag_IN", //  Magahi (India)
	"mai_IN", //  Maithili (India)
	"mg_MG", //  Malagasy (Madagascar)
	"mh_MH", //  Marshallese (Marshall Islands)
	"mhr_RU", //  Eastern Mari (Russia)
	"mi", //  Māori
	"mi_NZ", //  Māori (New Zealand)
	"miq_NI", //  Mískito (Nicaragua)
	"mk", //  Macedonian
	"mk_MK", //  Macedonian (Macedonia)
	"ml", //  Malayalam
	"ml_IN", //  Malayalam (India)
	"mni_IN", //  Manipuri (India)
	"mn_MN", //  Mongolian (Mongolia)
	"mr", //  Marathi
	"mr_IN", //  Marathi (India)
	"ms", //  Malay
	"ms_MY", //  Malay (Malaysia)
	"mt", //  Maltese
	"mt_MT", //  Maltese (Malta)
	"my_MM", //  Burmese (Myanmar)
	"myv_RU", //  Erzya (Russia)
	"nah_MX", //  Nahuatl languages (Mexico)
	"nan_TW", //  Min Nan Chinese (Taiwan)
	"nb", //  Norwegian Bokmål
	"nb_NO", //  Norwegian Bokmål (Norway)
	"nds_DE", //  Low German (Germany)
	"nds_NL", //  Low German (Netherlands)
	"ne_NP", //  Nepali (Nepal)
	"nhn_MX", //  Central Nahuatl (Mexico)
	"niu_NU", //  Niuean (Niue)
	"niu_NZ", //  Niuean (New Zealand)
	"nl", //  Dutch
	"nl_AW", //  Dutch (Aruba)
	"nl_BE", //  Dutch (Belgium)
	"nl_NL", //  Dutch (Netherlands)
	"nn", //  Norwegian Nynorsk
	"nn_NO", //  Norwegian Nynorsk (Norway)
	"nr_ZA", //  South Ndebele (South Africa)
	"nso_ZA", //  Pedi (South Africa)
	"oc_FR", //  Occitan (France)
	"om", //  Oromo
	"om_ET", //  Oromo (Ethiopia)
	"om_KE", //  Oromo (Kenya)
	"or", //  Oriya
	"or_IN", //  Oriya (India)
	"os_RU", //  Ossetian (Russia)
	"pa_IN", //  Panjabi (India)
	"pap", //  Papiamento
	"pap_AN", //  Papiamento (Netherlands Antilles)
	"pap_AW", //  Papiamento (Aruba)
	"pap_CW", //  Papiamento (Curaçao)
	"pa_PK", //  Panjabi (Pakistan)
	"pl", //  Polish
	"pl_PL", //  Polish (Poland)
	"pr", //  Pirate
	"ps_AF", //  Pushto (Afghanistan)
	"pt", //  Portuguese
	"pt_BR", //  Portuguese (Brazil)
	"pt_PT", //  Portuguese (Portugal)
	"quy_PE", //  Ayacucho Quechua (Peru)
	"quz_PE", //  Cusco Quechua (Peru)
	"raj_IN", //  Rajasthani (India)
	"ro", //  Romanian
	"ro_RO", //  Romanian (Romania)
	"ru", //  Russian
	"ru_RU", //  Russian (Russia)
	"ru_UA", //  Russian (Ukraine)
	"rw_RW", //  Kinyarwanda (Rwanda)
	"sa_IN", //  Sanskrit (India)
	"sat_IN", //  Santali (India)
	"sc_IT", //  Sardinian (Italy)
	"sco", //  Scots
	"sd_IN", //  Sindhi (India)
	"se_NO", //  Northern Sami (Norway)
	"sgs_LT", //  Samogitian (Lithuania)
	"shs_CA", //  Shuswap (Canada)
	"sid_ET", //  Sidamo (Ethiopia)
	"si", //  Sinhala
	"si_LK", //  Sinhala (Sri Lanka)
	"sk", //  Slovak
	"sk_SK", //  Slovak (Slovakia)
	"sl", //  Slovenian
	"sl_SI", //  Slovenian (Slovenia)
	"so", //  Somali
	"so_DJ", //  Somali (Djibouti)
	"so_ET", //  Somali (Ethiopia)
	"so_KE", //  Somali (Kenya)
	"so_SO", //  Somali (Somalia)
	"son_ML", //  Songhai languages (Mali)
	"sq", //  Albanian
	"sq_AL", //  Albanian (Albania)
	"sq_KV", //  Albanian (Kosovo)
	"sq_MK", //  Albanian (Macedonia)
	"sr", //  Serbian
	"sr_Cyrl", //  Serbian (Cyrillic)
	"sr_Latn", //  Serbian (Latin)
	"sr_ME", //  Serbian (Montenegro)
	"sr_RS", //  Serbian (Serbia)
	"ss_ZA", //  Swati (South Africa)
	"st_ZA", //  Southern Sotho (South Africa)
	"sv", //  Swedish
	"sv_FI", //  Swedish (Finland)
	"sv_SE", //  Swedish (Sweden)
	"sw_KE", //  Swahili (Kenya)
	"sw_TZ", //  Swahili (Tanzania)
	"szl_PL", //  Silesian (Poland)
	"ta", //  Tamil
	"ta_IN", //  Tamil (India)
	"ta_LK", //  Tamil (Sri Lanka)
	"tcy_IN", //  Tulu (India)
	"te", //  Telugu
	"te_IN", //  Telugu (India)
	"tg_TJ", //  Tajik (Tajikistan)
	"the_NP", //  Chitwania Tharu (Nepal)
	"th", //  Thai
	"th_TH", //  Thai (Thailand)
	"ti", //  Tigrinya
	"ti_ER", //  Tigrinya (Eritrea)
	"ti_ET", //  Tigrinya (Ethiopia)
	"tig_ER", //  Tigre (Eritrea)
	"tk_TM", //  Turkmen (Turkmenistan)
	"tl_PH", //  Tagalog (Philippines)
	"tn_ZA", //  Tswana (South Africa)
	"tr", //  Turkish
	"tr_CY", //  Turkish (Cyprus)
	"tr_TR", //  Turkish (Turkey)
	"ts_ZA", //  Tsonga (South Africa)
	"tt", //  Tatar
	"tt_RU", //  Tatar (Russia)
	"tzm", // Central Atlas Tamazight
	"tzm_MA", // Central Atlas Tamazight (Marrocos)
	"ug_CN", //  Uighur (China)
	"uk", //  Ukrainian
	"uk_UA", //  Ukrainian (Ukraine)
	"unm_US", //  Unami (United States)
	"ur", //  Urdu
	"ur_IN", //  Urdu (India)
	"ur_PK", //  Urdu (Pakistan)
	"uz", //  Uzbek
	"uz_UZ", //  Uzbek (Uzbekistan)
	"ve_ZA", //  Venda (South Africa)
	"vi", //  Vietnamese
	"vi_VN", //  Vietnamese (Vietnam)
	"wa_BE", //  Walloon (Belgium)
	"wae_CH", //  Walser (Switzerland)
	"wal_ET", //  Wolaytta (Ethiopia)
	"wo_SN", //  Wolof (Senegal)
	"xh_ZA", //  Xhosa (South Africa)
	"yi_US", //  Yiddish (United States)
	"yo_NG", //  Yoruba (Nigeria)
	"yue_HK", //  Yue Chinese (Hong Kong)
	"zh", //  Chinese
	"zh_CN", //  Chinese (China)
	"zh_HK", //  Chinese (Hong Kong)
	"zh_SG", //  Chinese (Singapore)
	"zh_TW", //  Chinese (Taiwan)
	"zu_ZA", //  Zulu (South Africa)
	nullptr
};

static const char *locale_names[] = {
	"Afar",
	"Afar (Djibouti)",
	"Afar (Eritrea)",
	"Afar (Ethiopia)",
	"Afrikaans",
	"Afrikaans (South Africa)",
	"Aguaruna (Peru)",
	"Akan (Ghana)",
	"Amharic (Ethiopia)",
	"Aragonese (Spain)",
	"Angika (India)",
	"Arabic",
	"Arabic (United Arab Emirates)",
	"Arabic (Bahrain)",
	"Arabic (Algeria)",
	"Arabic (Egypt)",
	"Arabic (India)",
	"Arabic (Iraq)",
	"Arabic (Jordan)",
	"Arabic (Kuwait)",
	"Arabic (Lebanon)",
	"Arabic (Libya)",
	"Arabic (Morocco)",
	"Arabic (Oman)",
	"Arabic (Qatar)",
	"Arabic (Saudi Arabia)",
	"Arabic (Sudan)",
	"Arabic (South Soudan)",
	"Arabic (Syria)",
	"Arabic (Tunisia)",
	"Arabic (Yemen)",
	"Assamese (India)",
	"Asturian (Spain)",
	"Southern Aymara (Peru)",
	"Aymara (Peru)",
	"Azerbaijani",
	"Azerbaijani (Azerbaijan)",
	"Belarusian",
	"Belarusian (Belarus)",
	"Bemba (Zambia)",
	"Berber languages (Algeria)",
	"Berber languages (Morocco)",
	"Bulgarian",
	"Bulgarian (Bulgaria)",
	"Bhili (India)",
	"Bhojpuri (India)",
	"Bislama (Tuvalu)",
	"Bengali",
	"Bengali (Bangladesh)",
	"Bengali (India)",
	"Tibetan",
	"Tibetan (China)",
	"Tibetan (India)",
	"Breton",
	"Breton (France)",
	"Bodo (India)",
	"Bosnian (Bosnia and Herzegovina)",
	"Bilin (Eritrea)",
	"Catalan",
	"Catalan (Andorra)",
	"Catalan (Spain)",
	"Catalan (France)",
	"Catalan (Italy)",
	"Chechen (Russia)",
	"Cherokee (United States)",
	"Mandarin Chinese (Taiwan)",
	"Crimean Tatar (Ukraine)",
	"Kashubian (Poland)",
	"Czech",
	"Czech (Czech Republic)",
	"Chuvash (Russia)",
	"Welsh (United Kingdom)",
	"Danish",
	"Danish (Denmark)",
	"German",
	"German (Austria)",
	"German (Belgium)",
	"German (Switzerland)",
	"German (Germany)",
	"German (Italy)",
	"German (Luxembourg)",
	"Dogri (India)",
	"Dhivehi (Maldives)",
	"Dzongkha (Bhutan)",
	"Greek",
	"Greek (Cyprus)",
	"Greek (Greece)",
	"English",
	"English (Antigua and Barbuda)",
	"English (Australia)",
	"English (Botswana)",
	"English (Canada)",
	"English (Denmark)",
	"English (United Kingdom)",
	"English (Hong Kong)",
	"English (Ireland)",
	"English (Israel)",
	"English (India)",
	"English (Nigeria)",
	"English (New Zealand)",
	"English (Philippines)",
	"English (Singapore)",
	"English (United States)",
	"English (South Africa)",
	"English (Zambia)",
	"English (Zimbabwe)",
	"Esperanto",
	"Spanish",
	"Spanish (Argentina)",
	"Spanish (Bolivia)",
	"Spanish (Chile)",
	"Spanish (Colombia)",
	"Spanish (Costa Rica)",
	"Spanish (Cuba)",
	"Spanish (Dominican Republic)",
	"Spanish (Ecuador)",
	"Spanish (Spain)",
	"Spanish (Guatemala)",
	"Spanish (Honduras)",
	"Spanish (Mexico)",
	"Spanish (Nicaragua)",
	"Spanish (Panama)",
	"Spanish (Peru)",
	"Spanish (Puerto Rico)",
	"Spanish (Paraguay)",
	"Spanish (El Salvador)",
	"Spanish (United States)",
	"Spanish (Uruguay)",
	"Spanish (Venezuela)",
	"Estonian",
	"Estonian (Estonia)",
	"Basque",
	"Basque (Spain)",
	"Persian",
	"Persian (Iran)",
	"Fulah (Senegal)",
	"Finnish",
	"Finnish (Finland)",
	"Filipino",
	"Filipino (Philippines)",
	"Faroese (Faroe Islands)",
	"French",
	"French (Belgium)",
	"French (Canada)",
	"French (Switzerland)",
	"French (France)",
	"French (Luxembourg)",
	"Friulian (Italy)",
	"Western Frisian (Germany)",
	"Western Frisian (Netherlands)",
	"Irish",
	"Irish (Ireland)",
	"Scottish Gaelic (United Kingdom)",
	"Geez (Eritrea)",
	"Geez (Ethiopia)",
	"Galician",
	"Galician (Spain)",
	"Gujarati (India)",
	"Manx (United Kingdom)",
	"Hakka Chinese (Taiwan)",
	"Hausa (Nigeria)",
	"Hebrew",
	"Hebrew (Israel)",
	"Hindi",
	"Hindi (India)",
	"Chhattisgarhi (India)",
	"Croatian",
	"Croatian (Croatia)",
	"Upper Sorbian (Germany)",
	"Haitian (Haiti)",
	"Hungarian",
	"Hungarian (Hungary)",
	"Huastec (Mexico)",
	"Armenian (Armenia)",
	"Interlingua (France)",
	"Indonesian",
	"Indonesian (Indonesia)",
	"Igbo (Nigeria)",
	"Inupiaq (Canada)",
	"Icelandic",
	"Icelandic (Iceland)",
	"Italian",
	"Italian (Switzerland)",
	"Italian (Italy)",
	"Inuktitut (Canada)",
	"Japanese",
	"Japanese (Japan)",
	"Kabyle (Algeria)",
	"Georgian",
	"Georgian (Georgia)",
	"Kazakh (Kazakhstan)",
	"Kalaallisut (Greenland)",
	"Central Khmer",
	"Central Khmer (Cambodia)",
	"Kannada (India)",
	"Konkani (India)",
	"Korean",
	"Korean (South Korea)",
	"Kashmiri (India)",
	"Kurdish",
	"Kurdish (Turkey)",
	"Cornish (United Kingdom)",
	"Kirghiz (Kyrgyzstan)",
	"Luxembourgish (Luxembourg)",
	"Ganda (Uganda)",
	"Limburgan (Belgium)",
	"Limburgan (Netherlands)",
	"Ligurian (Italy)",
	"Lingala (Congo)",
	"Lao (Laos)",
	"Lithuanian",
	"Lithuanian (Lithuania)",
	"Latvian",
	"Latvian (Latvia)",
	"Literary Chinese (Taiwan)",
	"Magahi (India)",
	"Maithili (India)",
	"Malagasy (Madagascar)",
	"Marshallese (Marshall Islands)",
	"Eastern Mari (Russia)",
	"Māori",
	"Māori (New Zealand)",
	"Mískito (Nicaragua)",
	"Macedonian",
	"Macedonian (Macedonia)",
	"Malayalam",
	"Malayalam (India)",
	"Manipuri (India)",
	"Mongolian (Mongolia)",
	"Marathi",
	"Marathi (India)",
	"Malay",
	"Malay (Malaysia)",
	"Maltese",
	"Maltese (Malta)",
	"Burmese (Myanmar)",
	"Erzya (Russia)",
	"Nahuatl languages (Mexico)",
	"Min Nan Chinese (Taiwan)",
	"Norwegian Bokmål",
	"Norwegian Bokmål (Norway)",
	"Low German (Germany)",
	"Low German (Netherlands)",
	"Nepali (Nepal)",
	"Central Nahuatl (Mexico)",
	"Niuean (Niue)",
	"Niuean (New Zealand)",
	"Dutch",
	"Dutch (Aruba)",
	"Dutch (Belgium)",
	"Dutch (Netherlands)",
	"Norwegian Nynorsk",
	"Norwegian Nynorsk (Norway)",
	"South Ndebele (South Africa)",
	"Pedi (South Africa)",
	"Occitan (France)",
	"Oromo",
	"Oromo (Ethiopia)",
	"Oromo (Kenya)",
	"Oriya",
	"Oriya (India)",
	"Ossetian (Russia)",
	"Panjabi (India)",
	"Papiamento",
	"Papiamento (Netherlands Antilles)",
	"Papiamento (Aruba)",
	"Papiamento (Curaçao)",
	"Panjabi (Pakistan)",
	"Polish",
	"Polish (Poland)",
	"Pirate",
	"Pushto (Afghanistan)",
	"Portuguese",
	"Portuguese (Brazil)",
	"Portuguese (Portugal)",
	"Ayacucho Quechua (Peru)",
	"Cusco Quechua (Peru)",
	"Rajasthani (India)",
	"Romanian",
	"Romanian (Romania)",
	"Russian",
	"Russian (Russia)",
	"Russian (Ukraine)",
	"Kinyarwanda (Rwanda)",
	"Sanskrit (India)",
	"Santali (India)",
	"Sardinian (Italy)",
	"Scots (Scotland)",
	"Sindhi (India)",
	"Northern Sami (Norway)",
	"Samogitian (Lithuania)",
	"Shuswap (Canada)",
	"Sidamo (Ethiopia)",
	"Sinhala",
	"Sinhala (Sri Lanka)",
	"Slovak",
	"Slovak (Slovakia)",
	"Slovenian",
	"Slovenian (Slovenia)",
	"Somali",
	"Somali (Djibouti)",
	"Somali (Ethiopia)",
	"Somali (Kenya)",
	"Somali (Somalia)",
	"Songhai languages (Mali)",
	"Albanian",
	"Albanian (Albania)",
	"Albanian (Kosovo)",
	"Albanian (Macedonia)",
	"Serbian",
	"Serbian (Cyrillic)",
	"Serbian (Latin)",
	"Serbian (Montenegro)",
	"Serbian (Serbia)",
	"Swati (South Africa)",
	"Southern Sotho (South Africa)",
	"Swedish",
	"Swedish (Finland)",
	"Swedish (Sweden)",
	"Swahili (Kenya)",
	"Swahili (Tanzania)",
	"Silesian (Poland)",
	"Tamil",
	"Tamil (India)",
	"Tamil (Sri Lanka)",
	"Tulu (India)",
	"Telugu",
	"Telugu (India)",
	"Tajik (Tajikistan)",
	"Chitwania Tharu (Nepal)",
	"Thai",
	"Thai (Thailand)",
	"Tigrinya",
	"Tigrinya (Eritrea)",
	"Tigrinya (Ethiopia)",
	"Tigre (Eritrea)",
	"Turkmen (Turkmenistan)",
	"Tagalog (Philippines)",
	"Tswana (South Africa)",
	"Turkish",
	"Turkish (Cyprus)",
	"Turkish (Turkey)",
	"Tsonga (South Africa)",
	"Tatar",
	"Tatar (Russia)",
	"Central Atlas Tamazight",
	"Central Atlas Tamazight (Marrocos)",
	"Uighur (China)",
	"Ukrainian",
	"Ukrainian (Ukraine)",
	"Unami (United States)",
	"Urdu",
	"Urdu (India)",
	"Urdu (Pakistan)",
	"Uzbek",
	"Uzbek (Uzbekistan)",
	"Venda (South Africa)",
	"Vietnamese",
	"Vietnamese (Vietnam)",
	"Walloon (Belgium)",
	"Walser (Switzerland)",
	"Wolaytta (Ethiopia)",
	"Wolof (Senegal)",
	"Xhosa (South Africa)",
	"Yiddish (United States)",
	"Yoruba (Nigeria)",
	"Yue Chinese (Hong Kong)",
	"Chinese",
	"Chinese (China)",
	"Chinese (Hong Kong)",
	"Chinese (Singapore)",
	"Chinese (Taiwan)",
	"Zulu (South Africa)",
	nullptr
};

// Windows has some weird locale identifiers which do not honor the ISO 639-1
// standardized nomenclature. Whenever those don't conflict with existing ISO
// identifiers, we override them.
//
// Reference:
// - https://msdn.microsoft.com/en-us/library/windows/desktop/ms693062(v=vs.85).aspx

static const char *locale_renames[][2] = {
	{ "in", "id" }, //  Indonesian
	{ "iw", "he" }, //  Hebrew
	{ "no", "nb" }, //  Norwegian Bokmål
	{ "C", "en" }, // Locale is not set, fallback to English.
	{ nullptr, nullptr }
};

// Additional script information to preferred scripts.
// Language code, script code, default country, supported countries.
// Reference:
// - https://lh.2xlibre.net/locales/
// - https://www.localeplanet.com/icu/index.html
// - https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-lcid/70feba9f-294e-491e-b6eb-56532684c37f

static const char *locale_scripts[][4] = {
	{ "az", "Latn", "", "AZ" },
	{ "az", "Arab", "", "IR" },
	{ "bs", "Latn", "", "BA" },
	{ "ff", "Latn", "", "BF,CM,GH,GM,GN,GW,LR,MR,NE,NG,SL,SN" },
	{ "pa", "Arab", "PK", "PK" },
	{ "pa", "Guru", "IN", "IN" },
	{ "sd", "Arab", "PK", "PK" },
	{ "sd", "Deva", "IN", "IN" },
	{ "shi", "Tfng", "", "MA" },
	{ "sr", "Cyrl", "", "BA,RS,XK" },
	{ "sr", "Latn", "", "ME" },
	{ "uz", "Latn", "", "UZ" },
	{ "uz", "Arab", "AF", "AF" },
	{ "vai", "Vaii", "", "LR" },
	{ "yue", "Hans", "CN", "CN" },
	{ "yue", "Hant", "HK", "HK" },
	{ "zh", "Hans", "CN", "CN,SG" },
	{ "zh", "Hant", "TW", "HK,MO,TW" },
	{ nullptr, nullptr, nullptr, nullptr }
};

// Additional mapping for outdated, temporary or exceptionally reserved country codes.
// Reference:
// - https://en.wikipedia.org/wiki/ISO_3166-1_alpha-2
// - https://www.iso.org/obp/ui/#search/code/

static const char *country_renames[][2] = {
	{ "BU", "MM" }, // Burma, name changed to Myanmar.
	{ "KV", "XK" }, // Kosovo (temporary FIPS code to European Commission code), no official ISO code assigned.
	{ "TP", "TL" }, // East Timor, name changed to Timor-Leste.
	{ "UK", "GB" }, // United Kingdom, exceptionally reserved code.
	{ nullptr, nullptr }
};

// Country code, country name.
// Reference:
// - https://en.wikipedia.org/wiki/ISO_3166-1_alpha-2
// - https://www.iso.org/obp/ui/#search/code/

static const char *country_names[][2] = {
	{ "AC", "Ascension Island" }, // Exceptionally reserved.
	{ "AD", "Andorra" },
	{ "AE", "United Arab Emirates" },
	{ "AF", "Afghanistan" },
	{ "AG", "Antigua and Barbuda" },
	{ "AI", "Anguilla" },
	{ "AL", "Albania" },
	{ "AM", "Armenia" },
	{ "AN", "Netherlands Antilles" }, // Transitionally reserved, divided into BQ, CW and SX.
	{ "AO", "Angola" },
	{ "AQ", "Antarctica" },
	{ "AR", "Argentina" },
	{ "AS", "American Samoa" },
	{ "AT", "Austria" },
	{ "AU", "Australia" },
	{ "AW", "Aruba" },
	{ "AX", "Åland Islands" },
	{ "AZ", "Azerbaijan" },
	{ "BA", "Bosnia and Herzegovina" },
	{ "BB", "Barbados" },
	{ "BD", "Bangladesh" },
	{ "BE", "Belgium" },
	{ "BF", "Burkina Faso" },
	{ "BG", "Bulgaria" },
	{ "BH", "Bahrain" },
	{ "BI", "Burundi" },
	{ "BJ", "Benin" },
	{ "BL", "St. Barthélemy" },
	{ "BM", "Bermuda" },
	{ "BN", "Brunei" },
	{ "BO", "Bolivia" },
	{ "BQ", "Caribbean Netherlands" },
	{ "BR", "Brazil" },
	{ "BS", "Bahamas" },
	{ "BT", "Bhutan" },
	{ "BV", "Bouvet Island" },
	{ "BW", "Botswana" },
	{ "BY", "Belarus" },
	{ "BZ", "Belize" },
	{ "CA", "Canada" },
	{ "CC", "Cocos (Keeling) Islands" },
	{ "CD", "Congo - Kinshasa" },
	{ "CF", "Central African Republic" },
	{ "CG", "Congo - Brazzaville" },
	{ "CH", "Switzerland" },
	{ "CI", "Côte d'Ivoire" },
	{ "CK", "Cook Islands" },
	{ "CL", "Chile" },
	{ "CM", "Cameroon" },
	{ "CN", "China" },
	{ "CO", "Colombia" },
	{ "CP", "Clipperton Island" }, // Exceptionally reserved.
	{ "CR", "Costa Rica" },
	{ "CQ", "Island of Sark" }, // Exceptionally reserved.
	{ "CU", "Cuba" },
	{ "CV", "Cabo Verde" },
	{ "CW", "Curaçao" },
	{ "CX", "Christmas Island" },
	{ "CY", "Cyprus" },
	{ "CZ", "Czechia" },
	{ "DE", "Germany" },
	{ "DG", "Diego Garcia" }, // Exceptionally reserved.
	{ "DJ", "Djibouti" },
	{ "DK", "Denmark" },
	{ "DM", "Dominica" },
	{ "DO", "Dominican Republic" },
	{ "DZ", "Algeria" },
	{ "EA", "Ceuta and Melilla" }, // Exceptionally reserved.
	{ "EC", "Ecuador" },
	{ "EE", "Estonia" },
	{ "EG", "Egypt" },
	{ "EH", "Western Sahara" },
	{ "ER", "Eritrea" },
	{ "ES", "Spain" },
	{ "ET", "Ethiopia" },
	{ "EU", "European Union" }, // Exceptionally reserved.
	{ "EZ", "Eurozone" }, // Exceptionally reserved.
	{ "FI", "Finland" },
	{ "FJ", "Fiji" },
	{ "FK", "Falkland Islands" },
	{ "FM", "Micronesia" },
	{ "FO", "Faroe Islands" },
	{ "FR", "France" },
	{ "FX", "France, Metropolitan" }, // Exceptionally reserved.
	{ "GA", "Gabon" },
	{ "GB", "United Kingdom" },
	{ "GD", "Grenada" },
	{ "GE", "Georgia" },
	{ "GF", "French Guiana" },
	{ "GG", "Guernsey" },
	{ "GH", "Ghana" },
	{ "GI", "Gibraltar" },
	{ "GL", "Greenland" },
	{ "GM", "Gambia" },
	{ "GN", "Guinea" },
	{ "GP", "Guadeloupe" },
	{ "GQ", "Equatorial Guinea" },
	{ "GR", "Greece" },
	{ "GS", "South Georgia and South Sandwich Islands" },
	{ "GT", "Guatemala" },
	{ "GU", "Guam" },
	{ "GW", "Guinea-Bissau" },
	{ "GY", "Guyana" },
	{ "HK", "Hong Kong" },
	{ "HM", "Heard Island and McDonald Islands" },
	{ "HN", "Honduras" },
	{ "HR", "Croatia" },
	{ "HT", "Haiti" },
	{ "HU", "Hungary" },
	{ "IC", "Canary Islands" }, // Exceptionally reserved.
	{ "ID", "Indonesia" },
	{ "IE", "Ireland" },
	{ "IL", "Israel" },
	{ "IM", "Isle of Man" },
	{ "IN", "India" },
	{ "IO", "British Indian Ocean Territory" },
	{ "IQ", "Iraq" },
	{ "IR", "Iran" },
	{ "IS", "Iceland" },
	{ "IT", "Italy" },
	{ "JE", "Jersey" },
	{ "JM", "Jamaica" },
	{ "JO", "Jordan" },
	{ "JP", "Japan" },
	{ "KE", "Kenya" },
	{ "KG", "Kyrgyzstan" },
	{ "KH", "Cambodia" },
	{ "KI", "Kiribati" },
	{ "KM", "Comoros" },
	{ "KN", "St. Kitts and Nevis" },
	{ "KP", "North Korea" },
	{ "KR", "South Korea" },
	{ "KW", "Kuwait" },
	{ "KY", "Cayman Islands" },
	{ "KZ", "Kazakhstan" },
	{ "LA", "Laos" },
	{ "LB", "Lebanon" },
	{ "LC", "St. Lucia" },
	{ "LI", "Liechtenstein" },
	{ "LK", "Sri Lanka" },
	{ "LR", "Liberia" },
	{ "LS", "Lesotho" },
	{ "LT", "Lithuania" },
	{ "LU", "Luxembourg" },
	{ "LV", "Latvia" },
	{ "LY", "Libya" },
	{ "MA", "Morocco" },
	{ "MC", "Monaco" },
	{ "MD", "Moldova" },
	{ "ME", "Montenegro" },
	{ "MF", "St. Martin" },
	{ "MG", "Madagascar" },
	{ "MH", "Marshall Islands" },
	{ "MK", "North Macedonia" },
	{ "ML", "Mali" },
	{ "MM", "Myanmar" },
	{ "MN", "Mongolia" },
	{ "MO", "Macao" },
	{ "MP", "Northern Mariana Islands" },
	{ "MQ", "Martinique" },
	{ "MR", "Mauritania" },
	{ "MS", "Montserrat" },
	{ "MT", "Malta" },
	{ "MU", "Mauritius" },
	{ "MV", "Maldives" },
	{ "MW", "Malawi" },
	{ "MX", "Mexico" },
	{ "MY", "Malaysia" },
	{ "MZ", "Mozambique" },
	{ "NA", "Namibia" },
	{ "NC", "New Caledonia" },
	{ "NE", "Niger" },
	{ "NF", "Norfolk Island" },
	{ "NG", "Nigeria" },
	{ "NI", "Nicaragua" },
	{ "NL", "Netherlands" },
	{ "NO", "Norway" },
	{ "NP", "Nepal" },
	{ "NR", "Nauru" },
	{ "NU", "Niue" },
	{ "NZ", "New Zealand" },
	{ "OM", "Oman" },
	{ "PA", "Panama" },
	{ "PE", "Peru" },
	{ "PF", "French Polynesia" },
	{ "PG", "Papua New Guinea" },
	{ "PH", "Philippines" },
	{ "PK", "Pakistan" },
	{ "PL", "Poland" },
	{ "PM", "St. Pierre and Miquelon" },
	{ "PN", "Pitcairn Islands" },
	{ "PR", "Puerto Rico" },
	{ "PS", "Palestine" },
	{ "PT", "Portugal" },
	{ "PW", "Palau" },
	{ "PY", "Paraguay" },
	{ "QA", "Qatar" },
	{ "RE", "Réunion" },
	{ "RO", "Romania" },
	{ "RS", "Serbia" },
	{ "RU", "Russia" },
	{ "RW", "Rwanda" },
	{ "SA", "Saudi Arabia" },
	{ "SB", "Solomon Islands" },
	{ "SC", "Seychelles" },
	{ "SD", "Sudan" },
	{ "SE", "Sweden" },
	{ "SG", "Singapore" },
	{ "SH", "St. Helena, Ascension and Tristan da Cunha" },
	{ "SI", "Slovenia" },
	{ "SJ", "Svalbard and Jan Mayen" },
	{ "SK", "Slovakia" },
	{ "SL", "Sierra Leone" },
	{ "SM", "San Marino" },
	{ "SN", "Senegal" },
	{ "SO", "Somalia" },
	{ "SR", "Suriname" },
	{ "SS", "South Sudan" },
	{ "ST", "Sao Tome and Principe" },
	{ "SV", "El Salvador" },
	{ "SX", "Sint Maarten" },
	{ "SY", "Syria" },
	{ "SZ", "Eswatini" },
	{ "TA", "Tristan da Cunha" }, // Exceptionally reserved.
	{ "TC", "Turks and Caicos Islands" },
	{ "TD", "Chad" },
	{ "TF", "French Southern Territories" },
	{ "TG", "Togo" },
	{ "TH", "Thailand" },
	{ "TJ", "Tajikistan" },
	{ "TK", "Tokelau" },
	{ "TL", "Timor-Leste" },
	{ "TM", "Turkmenistan" },
	{ "TN", "Tunisia" },
	{ "TO", "Tonga" },
	{ "TR", "Turkey" },
	{ "TT", "Trinidad and Tobago" },
	{ "TV", "Tuvalu" },
	{ "TW", "Taiwan" },
	{ "TZ", "Tanzania" },
	{ "UA", "Ukraine" },
	{ "UG", "Uganda" },
	{ "UM", "U.S. Outlying Islands" },
	{ "US", "United States of America" },
	{ "UY", "Uruguay" },
	{ "UZ", "Uzbekistan" },
	{ "VA", "Holy See" },
	{ "VC", "St. Vincent and the Grenadines" },
	{ "VE", "Venezuela" },
	{ "VG", "British Virgin Islands" },
	{ "VI", "U.S. Virgin Islands" },
	{ "VN", "Viet Nam" },
	{ "VU", "Vanuatu" },
	{ "WF", "Wallis and Futuna" },
	{ "WS", "Samoa" },
	{ "XK", "Kosovo" }, // Temporary code, no official ISO code assigned.
	{ "YE", "Yemen" },
	{ "YT", "Mayotte" },
	{ "ZA", "South Africa" },
	{ "ZM", "Zambia" },
	{ "ZW", "Zimbabwe" },
	{ nullptr, nullptr }
};

// Languages code, language name.
// Reference:
// - https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes
// - https://www.localeplanet.com/icu/index.html
// - https://lh.2xlibre.net/locales/

static const char *language_list[][2] = {
	{ "aa", "Afar" },
	{ "ab", "Abkhazian" },
	{ "ace", "Achinese" },
	{ "ach", "Acoli" },
	{ "ada", "Adangme" },
	{ "ady", "Adyghe" },
	{ "ae", "Avestan" },
	{ "aeb", "Tunisian Arabic" },
	{ "af", "Afrikaans" },
	{ "afh", "Afrihili" },
	{ "agq", "Aghem" },
	{ "ain", "Ainu" },
	{ "agr", "Aguaruna" },
	{ "ak", "Akan" },
	{ "akk", "Akkadian" },
	{ "akz", "Alabama" },
	{ "ale", "Aleut" },
	{ "aln", "Gheg Albanian" },
	{ "alt", "Southern Altai" },
	{ "am", "Amharic" },
	{ "an", "Aragonese" },
	{ "ang", "Old English" },
	{ "anp", "Angika" },
	{ "ar", "Arabic" },
	{ "arc", "Aramaic" },
	{ "arn", "Mapudungun" },
	{ "aro", "Araona" },
	{ "arp", "Arapaho" },
	{ "arq", "Algerian Arabic" },
	{ "ars", "Najdi Arabic" },
	{ "arw", "Arawak" },
	{ "ary", "Moroccan Arabic" },
	{ "arz", "Egyptian Arabic" },
	{ "as", "Assamese" },
	{ "asa", "Asu" },
	{ "ase", "American Sign Language" },
	{ "ast", "Asturian" },
	{ "av", "Avaric" },
	{ "avk", "Kotava" },
	{ "awa", "Awadhi" },
	{ "ayc", "Southern Aymara" },
	{ "ay", "Aymara" },
	{ "az", "Azerbaijani" },
	{ "ba", "Bashkir" },
	{ "bal", "Baluchi" },
	{ "ban", "Balinese" },
	{ "bar", "Bavarian" },
	{ "bas", "Bassa" },
	{ "bax", "Bamun" },
	{ "bbc", "Batak Toba" },
	{ "bbj", "Ghomala" },
	{ "be", "Belarusian" },
	{ "bej", "Beja" },
	{ "bem", "Bemba" },
	{ "ber", "Berber" },
	{ "bew", "Betawi" },
	{ "bez", "Bena" },
	{ "bfd", "Bafut" },
	{ "bfq", "Badaga" },
	{ "bg", "Bulgarian" },
	{ "bhb", "Bhili" },
	{ "bgn", "Western Balochi" },
	{ "bho", "Bhojpuri" },
	{ "bi", "Bislama" },
	{ "bik", "Bikol" },
	{ "bin", "Bini" },
	{ "bjn", "Banjar" },
	{ "bkm", "Kom" },
	{ "bla", "Siksika" },
	{ "bm", "Bambara" },
	{ "bn", "Bengali" },
	{ "bo", "Tibetan" },
	{ "bpy", "Bishnupriya" },
	{ "bqi", "Bakhtiari" },
	{ "br", "Breton" },
	{ "brh", "Brahui" },
	{ "brx", "Bodo" },
	{ "bs", "Bosnian" },
	{ "bss", "Akoose" },
	{ "bua", "Buriat" },
	{ "bug", "Buginese" },
	{ "bum", "Bulu" },
	{ "byn", "Bilin" },
	{ "byv", "Medumba" },
	{ "ca", "Catalan" },
	{ "cad", "Caddo" },
	{ "car", "Carib" },
	{ "cay", "Cayuga" },
	{ "cch", "Atsam" },
	{ "ccp", "Chakma" },
	{ "ce", "Chechen" },
	{ "ceb", "Cebuano" },
	{ "cgg", "Chiga" },
	{ "ch", "Chamorro" },
	{ "chb", "Chibcha" },
	{ "chg", "Chagatai" },
	{ "chk", "Chuukese" },
	{ "chm", "Mari" },
	{ "chn", "Chinook Jargon" },
	{ "cho", "Choctaw" },
	{ "chp", "Chipewyan" },
	{ "chr", "Cherokee" },
	{ "chy", "Cheyenne" },
	{ "cic", "Chickasaw" },
	{ "ckb", "Central Kurdish" },
	{ "csb", "Kashubian" },
	{ "cmn", "Mandarin Chinese" },
	{ "co", "Corsican" },
	{ "cop", "Coptic" },
	{ "cps", "Capiznon" },
	{ "cr", "Cree" },
	{ "crh", "Crimean Tatar" },
	{ "crs", "Seselwa Creole French" },
	{ "cs", "Czech" },
	{ "csb", "Kashubian" },
	{ "cu", "Church Slavic" },
	{ "cv", "Chuvash" },
	{ "cy", "Welsh" },
	{ "da", "Danish" },
	{ "dak", "Dakota" },
	{ "dar", "Dargwa" },
	{ "dav", "Taita" },
	{ "de", "German" },
	{ "del", "Delaware" },
	{ "den", "Slave" },
	{ "dgr", "Dogrib" },
	{ "din", "Dinka" },
	{ "dje", "Zarma" },
	{ "doi", "Dogri" },
	{ "dsb", "Lower Sorbian" },
	{ "dtp", "Central Dusun" },
	{ "dua", "Duala" },
	{ "dum", "Middle Dutch" },
	{ "dv", "Dhivehi" },
	{ "dyo", "Jola-Fonyi" },
	{ "dyu", "Dyula" },
	{ "dz", "Dzongkha" },
	{ "dzg", "Dazaga" },
	{ "ebu", "Embu" },
	{ "ee", "Ewe" },
	{ "efi", "Efik" },
	{ "egl", "Emilian" },
	{ "egy", "Ancient Egyptian" },
	{ "eka", "Ekajuk" },
	{ "el", "Greek" },
	{ "elx", "Elamite" },
	{ "en", "English" },
	{ "enm", "Middle English" },
	{ "eo", "Esperanto" },
	{ "es", "Spanish" },
	{ "esu", "Central Yupik" },
	{ "et", "Estonian" },
	{ "eu", "Basque" },
	{ "ewo", "Ewondo" },
	{ "ext", "Extremaduran" },
	{ "fa", "Persian" },
	{ "fan", "Fang" },
	{ "fat", "Fanti" },
	{ "ff", "Fulah" },
	{ "fi", "Finnish" },
	{ "fil", "Filipino" },
	{ "fit", "Tornedalen Finnish" },
	{ "fj", "Fijian" },
	{ "fo", "Faroese" },
	{ "fon", "Fon" },
	{ "fr", "French" },
	{ "frc", "Cajun French" },
	{ "frm", "Middle French" },
	{ "fro", "Old French" },
	{ "frp", "Arpitan" },
	{ "frr", "Northern Frisian" },
	{ "frs", "Eastern Frisian" },
	{ "fur", "Friulian" },
	{ "fy", "Western Frisian" },
	{ "ga", "Irish" },
	{ "gaa", "Ga" },
	{ "gag", "Gagauz" },
	{ "gan", "Gan Chinese" },
	{ "gay", "Gayo" },
	{ "gba", "Gbaya" },
	{ "gbz", "Zoroastrian Dari" },
	{ "gd", "Scottish Gaelic" },
	{ "gez", "Geez" },
	{ "gil", "Gilbertese" },
	{ "gl", "Galician" },
	{ "glk", "Gilaki" },
	{ "gmh", "Middle High German" },
	{ "gn", "Guarani" },
	{ "goh", "Old High German" },
	{ "gom", "Goan Konkani" },
	{ "gon", "Gondi" },
	{ "gor", "Gorontalo" },
	{ "got", "Gothic" },
	{ "grb", "Grebo" },
	{ "grc", "Ancient Greek" },
	{ "gsw", "Swiss German" },
	{ "gu", "Gujarati" },
	{ "guc", "Wayuu" },
	{ "gur", "Frafra" },
	{ "guz", "Gusii" },
	{ "gv", "Manx" },
	{ "gwi", "Gwichʼin" },
	{ "ha", "Hausa" },
	{ "hai", "Haida" },
	{ "hak", "Hakka Chinese" },
	{ "haw", "Hawaiian" },
	{ "he", "Hebrew" },
	{ "hi", "Hindi" },
	{ "hif", "Fiji Hindi" },
	{ "hil", "Hiligaynon" },
	{ "hit", "Hittite" },
	{ "hmn", "Hmong" },
	{ "ho", "Hiri Motu" },
	{ "hne", "Chhattisgarhi" },
	{ "hr", "Croatian" },
	{ "hsb", "Upper Sorbian" },
	{ "hsn", "Xiang Chinese" },
	{ "ht", "Haitian" },
	{ "hu", "Hungarian" },
	{ "hup", "Hupa" },
	{ "hus", "Huastec" },
	{ "hy", "Armenian" },
	{ "hz", "Herero" },
	{ "ia", "Interlingua" },
	{ "iba", "Iban" },
	{ "ibb", "Ibibio" },
	{ "id", "Indonesian" },
	{ "ie", "Interlingue" },
	{ "ig", "Igbo" },
	{ "ii", "Sichuan Yi" },
	{ "ik", "Inupiaq" },
	{ "ilo", "Iloko" },
	{ "inh", "Ingush" },
	{ "io", "Ido" },
	{ "is", "Icelandic" },
	{ "it", "Italian" },
	{ "iu", "Inuktitut" },
	{ "izh", "Ingrian" },
	{ "ja", "Japanese" },
	{ "jam", "Jamaican Creole English" },
	{ "jbo", "Lojban" },
	{ "jgo", "Ngomba" },
	{ "jmc", "Machame" },
	{ "jpr", "Judeo-Persian" },
	{ "jrb", "Judeo-Arabic" },
	{ "jut", "Jutish" },
	{ "jv", "Javanese" },
	{ "ka", "Georgian" },
	{ "kaa", "Kara-Kalpak" },
	{ "kab", "Kabyle" },
	{ "kac", "Kachin" },
	{ "kaj", "Jju" },
	{ "kam", "Kamba" },
	{ "kaw", "Kawi" },
	{ "kbd", "Kabardian" },
	{ "kbl", "Kanembu" },
	{ "kcg", "Tyap" },
	{ "kde", "Makonde" },
	{ "kea", "Kabuverdianu" },
	{ "ken", "Kenyang" },
	{ "kfo", "Koro" },
	{ "kg", "Kongo" },
	{ "kgp", "Kaingang" },
	{ "kha", "Khasi" },
	{ "kho", "Khotanese" },
	{ "khq", "Koyra Chiini" },
	{ "khw", "Khowar" },
	{ "ki", "Kikuyu" },
	{ "kiu", "Kirmanjki" },
	{ "kj", "Kuanyama" },
	{ "kk", "Kazakh" },
	{ "kkj", "Kako" },
	{ "kl", "Kalaallisut" },
	{ "kln", "Kalenjin" },
	{ "km", "Central Khmer" },
	{ "kmb", "Kimbundu" },
	{ "kn", "Kannada" },
	{ "ko", "Korean" },
	{ "koi", "Komi-Permyak" },
	{ "kok", "Konkani" },
	{ "kos", "Kosraean" },
	{ "kpe", "Kpelle" },
	{ "kr", "Kanuri" },
	{ "krc", "Karachay-Balkar" },
	{ "kri", "Krio" },
	{ "krj", "Kinaray-a" },
	{ "krl", "Karelian" },
	{ "kru", "Kurukh" },
	{ "ks", "Kashmiri" },
	{ "ksb", "Shambala" },
	{ "ksf", "Bafia" },
	{ "ksh", "Colognian" },
	{ "ku", "Kurdish" },
	{ "kum", "Kumyk" },
	{ "kut", "Kutenai" },
	{ "kv", "Komi" },
	{ "kw", "Cornish" },
	{ "ky", "Kirghiz" },
	{ "lag", "Langi" },
	{ "la", "Latin" },
	{ "lad", "Ladino" },
	{ "lag", "Langi" },
	{ "lah", "Lahnda" },
	{ "lam", "Lamba" },
	{ "lb", "Luxembourgish" },
	{ "lez", "Lezghian" },
	{ "lfn", "Lingua Franca Nova" },
	{ "lg", "Ganda" },
	{ "li", "Limburgan" },
	{ "lij", "Ligurian" },
	{ "liv", "Livonian" },
	{ "lkt", "Lakota" },
	{ "lmo", "Lombard" },
	{ "ln", "Lingala" },
	{ "lo", "Lao" },
	{ "lol", "Mongo" },
	{ "lou", "Louisiana Creole" },
	{ "loz", "Lozi" },
	{ "lrc", "Northern Luri" },
	{ "lt", "Lithuanian" },
	{ "ltg", "Latgalian" },
	{ "lu", "Luba-Katanga" },
	{ "lua", "Luba-Lulua" },
	{ "lui", "Luiseno" },
	{ "lun", "Lunda" },
	{ "luo", "Luo" },
	{ "lus", "Mizo" },
	{ "luy", "Luyia" },
	{ "lv", "Latvian" },
	{ "lzh", "Literary Chinese" },
	{ "lzz", "Laz" },
	{ "mad", "Madurese" },
	{ "maf", "Mafa" },
	{ "mag", "Magahi" },
	{ "mai", "Maithili" },
	{ "mak", "Makasar" },
	{ "man", "Mandingo" },
	{ "mas", "Masai" },
	{ "mde", "Maba" },
	{ "mdf", "Moksha" },
	{ "mdr", "Mandar" },
	{ "men", "Mende" },
	{ "mer", "Meru" },
	{ "mfe", "Morisyen" },
	{ "mg", "Malagasy" },
	{ "mga", "Middle Irish" },
	{ "mgh", "Makhuwa-Meetto" },
	{ "mgo", "Metaʼ" },
	{ "mh", "Marshallese" },
	{ "mhr", "Eastern Mari" },
	{ "mi", "Māori" },
	{ "mic", "Mi'kmaq" },
	{ "min", "Minangkabau" },
	{ "miq", "Mískito" },
	{ "mjw", "Karbi" },
	{ "mk", "Macedonian" },
	{ "ml", "Malayalam" },
	{ "mn", "Mongolian" },
	{ "mnc", "Manchu" },
	{ "mni", "Manipuri" },
	{ "mnw", "Mon" },
	{ "mos", "Mossi" },
	{ "moh", "Mohawk" },
	{ "mr", "Marathi" },
	{ "mrj", "Western Mari" },
	{ "ms", "Malay" },
	{ "mt", "Maltese" },
	{ "mua", "Mundang" },
	{ "mus", "Muscogee" },
	{ "mwl", "Mirandese" },
	{ "mwr", "Marwari" },
	{ "mwv", "Mentawai" },
	{ "my", "Burmese" },
	{ "mye", "Myene" },
	{ "myv", "Erzya" },
	{ "mzn", "Mazanderani" },
	{ "na", "Nauru" },
	{ "nah", "Nahuatl" },
	{ "nan", "Min Nan Chinese" },
	{ "nap", "Neapolitan" },
	{ "naq", "Nama" },
	{ "nan", "Min Nan Chinese" },
	{ "nb", "Norwegian Bokmål" },
	{ "nd", "North Ndebele" },
	{ "nds", "Low German" },
	{ "ne", "Nepali" },
	{ "new", "Newari" },
	{ "nhn", "Central Nahuatl" },
	{ "ng", "Ndonga" },
	{ "nia", "Nias" },
	{ "niu", "Niuean" },
	{ "njo", "Ao Naga" },
	{ "nl", "Dutch" },
	{ "nmg", "Kwasio" },
	{ "nn", "Norwegian Nynorsk" },
	{ "nnh", "Ngiemboon" },
	{ "nog", "Nogai" },
	{ "non", "Old Norse" },
	{ "nov", "Novial" },
	{ "nqo", "N'ko" },
	{ "nr", "South Ndebele" },
	{ "nso", "Pedi" },
	{ "nus", "Nuer" },
	{ "nv", "Navajo" },
	{ "nwc", "Classical Newari" },
	{ "ny", "Nyanja" },
	{ "nym", "Nyamwezi" },
	{ "nyn", "Nyankole" },
	{ "nyo", "Nyoro" },
	{ "nzi", "Nzima" },
	{ "oc", "Occitan" },
	{ "oj", "Ojibwa" },
	{ "om", "Oromo" },
	{ "or", "Odia" },
	{ "os", "Ossetic" },
	{ "osa", "Osage" },
	{ "ota", "Ottoman Turkish" },
	{ "pa", "Panjabi" },
	{ "pag", "Pangasinan" },
	{ "pal", "Pahlavi" },
	{ "pam", "Pampanga" },
	{ "pap", "Papiamento" },
	{ "pau", "Palauan" },
	{ "pcd", "Picard" },
	{ "pcm", "Nigerian Pidgin" },
	{ "pdc", "Pennsylvania German" },
	{ "pdt", "Plautdietsch" },
	{ "peo", "Old Persian" },
	{ "pfl", "Palatine German" },
	{ "phn", "Phoenician" },
	{ "pi", "Pali" },
	{ "pl", "Polish" },
	{ "pms", "Piedmontese" },
	{ "pnt", "Pontic" },
	{ "pon", "Pohnpeian" },
	{ "pr", "Pirate" },
	{ "prg", "Prussian" },
	{ "pro", "Old Provençal" },
	{ "prs", "Dari" },
	{ "ps", "Pushto" },
	{ "pt", "Portuguese" },
	{ "qu", "Quechua" },
	{ "quc", "K'iche" },
	{ "qug", "Chimborazo Highland Quichua" },
	{ "quy", "Ayacucho Quechua" },
	{ "quz", "Cusco Quechua" },
	{ "raj", "Rajasthani" },
	{ "rap", "Rapanui" },
	{ "rar", "Rarotongan" },
	{ "rgn", "Romagnol" },
	{ "rif", "Riffian" },
	{ "rm", "Romansh" },
	{ "rn", "Rundi" },
	{ "ro", "Romanian" },
	{ "rof", "Rombo" },
	{ "rom", "Romany" },
	{ "rtm", "Rotuman" },
	{ "ru", "Russian" },
	{ "rue", "Rusyn" },
	{ "rug", "Roviana" },
	{ "rup", "Aromanian" },
	{ "rw", "Kinyarwanda" },
	{ "rwk", "Rwa" },
	{ "sa", "Sanskrit" },
	{ "sad", "Sandawe" },
	{ "sah", "Sakha" },
	{ "sam", "Samaritan Aramaic" },
	{ "saq", "Samburu" },
	{ "sas", "Sasak" },
	{ "sat", "Santali" },
	{ "saz", "Saurashtra" },
	{ "sba", "Ngambay" },
	{ "sbp", "Sangu" },
	{ "sc", "Sardinian" },
	{ "scn", "Sicilian" },
	{ "sco", "Scots" },
	{ "sd", "Sindhi" },
	{ "sdc", "Sassarese Sardinian" },
	{ "sdh", "Southern Kurdish" },
	{ "se", "Northern Sami" },
	{ "see", "Seneca" },
	{ "seh", "Sena" },
	{ "sei", "Seri" },
	{ "sel", "Selkup" },
	{ "ses", "Koyraboro Senni" },
	{ "sg", "Sango" },
	{ "sga", "Old Irish" },
	{ "sgs", "Samogitian" },
	{ "sh", "Serbo-Croatian" },
	{ "shi", "Tachelhit" },
	{ "shn", "Shan" },
	{ "shs", "Shuswap" },
	{ "shu", "Chadian Arabic" },
	{ "si", "Sinhala" },
	{ "sid", "Sidamo" },
	{ "sk", "Slovak" },
	{ "sl", "Slovenian" },
	{ "sli", "Lower Silesian" },
	{ "sly", "Selayar" },
	{ "sm", "Samoan" },
	{ "sma", "Southern Sami" },
	{ "smj", "Lule Sami" },
	{ "smn", "Inari Sami" },
	{ "sms", "Skolt Sami" },
	{ "sn", "Shona" },
	{ "snk", "Soninke" },
	{ "so", "Somali" },
	{ "sog", "Sogdien" },
	{ "son", "Songhai" },
	{ "sq", "Albanian" },
	{ "sr", "Serbian" },
	{ "srn", "Sranan Tongo" },
	{ "srr", "Serer" },
	{ "ss", "Swati" },
	{ "ssy", "Saho" },
	{ "st", "Southern Sotho" },
	{ "stq", "Saterland Frisian" },
	{ "su", "Sundanese" },
	{ "suk", "Sukuma" },
	{ "sus", "Susu" },
	{ "sux", "Sumerian" },
	{ "sv", "Swedish" },
	{ "sw", "Swahili" },
	{ "swb", "Comorian" },
	{ "swc", "Congo Swahili" },
	{ "syc", "Classical Syriac" },
	{ "syr", "Syriac" },
	{ "szl", "Silesian" },
	{ "ta", "Tamil" },
	{ "tcy", "Tulu" },
	{ "te", "Telugu" },
	{ "tem", "Timne" },
	{ "teo", "Teso" },
	{ "ter", "Tereno" },
	{ "tet", "Tetum" },
	{ "tg", "Tajik" },
	{ "th", "Thai" },
	{ "the", "Chitwania Tharu" },
	{ "ti", "Tigrinya" },
	{ "tig", "Tigre" },
	{ "tiv", "Tiv" },
	{ "tk", "Turkmen" },
	{ "tkl", "Tokelau" },
	{ "tkr", "Tsakhur" },
	{ "tl", "Tagalog" },
	{ "tlh", "Klingon" },
	{ "tli", "Tlingit" },
	{ "tly", "Talysh" },
	{ "tmh", "Tamashek" },
	{ "tn", "Tswana" },
	{ "to", "Tongan" },
	{ "tog", "Nyasa Tonga" },
	{ "tpi", "Tok Pisin" },
	{ "tr", "Turkish" },
	{ "tru", "Turoyo" },
	{ "trv", "Taroko" },
	{ "ts", "Tsonga" },
	{ "tsd", "Tsakonian" },
	{ "tsi", "Tsimshian" },
	{ "tt", "Tatar" },
	{ "ttt", "Muslim Tat" },
	{ "tum", "Tumbuka" },
	{ "tvl", "Tuvalu" },
	{ "tw", "Twi" },
	{ "twq", "Tasawaq" },
	{ "ty", "Tahitian" },
	{ "tyv", "Tuvinian" },
	{ "tzm", "Central Atlas Tamazight" },
	{ "udm", "Udmurt" },
	{ "ug", "Uyghur" },
	{ "uga", "Ugaritic" },
	{ "uk", "Ukrainian" },
	{ "umb", "Umbundu" },
	{ "unm", "Unami" },
	{ "ur", "Urdu" },
	{ "uz", "Uzbek" },
	{ "vai", "Vai" },
	{ "ve", "Venda" },
	{ "vec", "Venetian" },
	{ "vep", "Veps" },
	{ "vi", "Vietnamese" },
	{ "vls", "West Flemish" },
	{ "vmf", "Main-Franconian" },
	{ "vo", "Volapük" },
	{ "vot", "Votic" },
	{ "vro", "Võro" },
	{ "vun", "Vunjo" },
	{ "wa", "Walloon" },
	{ "wae", "Walser" },
	{ "wal", "Wolaytta" },
	{ "war", "Waray" },
	{ "was", "Washo" },
	{ "wbp", "Warlpiri" },
	{ "wo", "Wolof" },
	{ "wuu", "Wu Chinese" },
	{ "xal", "Kalmyk" },
	{ "xh", "Xhosa" },
	{ "xmf", "Mingrelian" },
	{ "xog", "Soga" },
	{ "yao", "Yao" },
	{ "yap", "Yapese" },
	{ "yav", "Yangben" },
	{ "ybb", "Yemba" },
	{ "yi", "Yiddish" },
	{ "yo", "Yoruba" },
	{ "yrl", "Nheengatu" },
	{ "yue", "Yue Chinese" },
	{ "yuw", "Papua New Guinea" },
	{ "za", "Zhuang" },
	{ "zap", "Zapotec" },
	{ "zbl", "Blissymbols" },
	{ "zea", "Zeelandic" },
	{ "zen", "Zenaga" },
	{ "zgh", "Standard Moroccan Tamazight" },
	{ "zh", "Chinese" },
	{ "zu", "Zulu" },
	{ "zun", "Zuni" },
	{ "zza", "Zaza" },
	{ nullptr, nullptr }
};

// Additional regional variants.
// Variant name, supported languages.

static const char *locale_variants[][2] = {
	{ "valencia", "ca" },
	{ "iqtelif", "tt" },
	{ "saaho", "aa" },
	{ "tradnl", "es" },
	{ nullptr, nullptr },
};

// Script names and codes (excludes typographic variants, special codes, reserved codes and aliases for combined scripts).
// Reference:
// - https://en.wikipedia.org/wiki/ISO_15924

static const char *script_list[][2] = {
	{ "Adlam", "Adlm" },
	{ "Afaka", "Afak" },
	{ "Caucasian Albanian", "Aghb" },
	{ "Ahom", "Ahom" },
	{ "Arabic", "Arab" },
	{ "Imperial Aramaic", "Armi" },
	{ "Armenian", "Armn" },
	{ "Avestan", "Avst" },
	{ "Balinese", "Bali" },
	{ "Bamum", "Bamu" },
	{ "Bassa Vah", "Bass" },
	{ "Batak", "Batk" },
	{ "Bengali", "Beng" },
	{ "Bhaiksuki", "Bhks" },
	{ "Blissymbols", "Blis" },
	{ "Bopomofo", "Bopo" },
	{ "Brahmi", "Brah" },
	{ "Braille", "Brai" },
	{ "Buginese", "Bugi" },
	{ "Buhid", "Buhd" },
	{ "Chakma", "Cakm" },
	{ "Unified Canadian Aboriginal", "Cans" },
	{ "Carian", "Cari" },
	{ "Cham", "Cham" },
	{ "Cherokee", "Cher" },
	{ "Chorasmian", "Chrs" },
	{ "Cirth", "Cirt" },
	{ "Coptic", "Copt" },
	{ "Cypro-Minoan", "Cpmn" },
	{ "Cypriot", "Cprt" },
	{ "Cyrillic", "Cyrl" },
	{ "Devanagari", "Deva" },
	{ "Dives Akuru", "Diak" },
	{ "Dogra", "Dogr" },
	{ "Deseret", "Dsrt" },
	{ "Duployan", "Dupl" },
	{ "Egyptian demotic", "Egyd" },
	{ "Egyptian hieratic", "Egyh" },
	{ "Egyptian hieroglyphs", "Egyp" },
	{ "Elbasan", "Elba" },
	{ "Elymaic", "Elym" },
	{ "Ethiopic", "Ethi" },
	{ "Khutsuri", "Geok" },
	{ "Georgian", "Geor" },
	{ "Glagolitic", "Glag" },
	{ "Gunjala Gondi", "Gong" },
	{ "Masaram Gondi", "Gonm" },
	{ "Gothic", "Goth" },
	{ "Grantha", "Gran" },
	{ "Greek", "Grek" },
	{ "Gujarati", "Gujr" },
	{ "Gurmukhi", "Guru" },
	{ "Hangul", "Hang" },
	{ "Han", "Hani" },
	{ "Hanunoo", "Hano" },
	{ "Simplified", "Hans" },
	{ "Traditional", "Hant" },
	{ "Hatran", "Hatr" },
	{ "Hebrew", "Hebr" },
	{ "Hiragana", "Hira" },
	{ "Anatolian Hieroglyphs", "Hluw" },
	{ "Pahawh Hmong", "Hmng" },
	{ "Nyiakeng Puachue Hmong", "Hmnp" },
	{ "Old Hungarian", "Hung" },
	{ "Indus", "Inds" },
	{ "Old Italic", "Ital" },
	{ "Javanese", "Java" },
	{ "Jurchen", "Jurc" },
	{ "Kayah Li", "Kali" },
	{ "Katakana", "Kana" },
	{ "Kawi", "Kawi" },
	{ "Kharoshthi", "Khar" },
	{ "Khmer", "Khmr" },
	{ "Khojki", "Khoj" },
	{ "Khitan large script", "Kitl" },
	{ "Khitan small script", "Kits" },
	{ "Kannada", "Knda" },
	{ "Kpelle", "Kpel" },
	{ "Kaithi", "Kthi" },
	{ "Tai Tham", "Lana" },
	{ "Lao", "Laoo" },
	{ "Latin", "Latn" },
	{ "Leke", "Leke" },
	{ "Lepcha", "Lepc" },
	{ "Limbu", "Limb" },
	{ "Linear A", "Lina" },
	{ "Linear B", "Linb" },
	{ "Lisu", "Lisu" },
	{ "Loma", "Loma" },
	{ "Lycian", "Lyci" },
	{ "Lydian", "Lydi" },
	{ "Mahajani", "Mahj" },
	{ "Makasar", "Maka" },
	{ "Mandaic", "Mand" },
	{ "Manichaean", "Mani" },
	{ "Marchen", "Marc" },
	{ "Mayan Hieroglyphs", "Maya" },
	{ "Medefaidrin", "Medf" },
	{ "Mende Kikakui", "Mend" },
	{ "Meroitic Cursive", "Merc" },
	{ "Meroitic Hieroglyphs", "Mero" },
	{ "Malayalam", "Mlym" },
	{ "Modi", "Modi" },
	{ "Mongolian", "Mong" },
	{ "Moon", "Moon" },
	{ "Mro", "Mroo" },
	{ "Meitei Mayek", "Mtei" },
	{ "Multani", "Mult" },
	{ "Myanmar (Burmese)", "Mymr" },
	{ "​Nag Mundari", "Nagm" },
	{ "Nandinagari", "Nand" },
	{ "Old North Arabian", "Narb" },
	{ "Nabataean", "Nbat" },
	{ "Newa", "Newa" },
	{ "Naxi Dongba", "Nkdb" },
	{ "Nakhi Geba", "Nkgb" },
	{ "N'ko", "Nkoo" },
	{ "Nüshu", "Nshu" },
	{ "Ogham", "Ogam" },
	{ "Ol Chiki", "Olck" },
	{ "Old Turkic", "Orkh" },
	{ "Oriya", "Orya" },
	{ "Osage", "Osge" },
	{ "Osmanya", "Osma" },
	{ "Old Uyghur", "Ougr" },
	{ "Palmyrene", "Palm" },
	{ "Pau Cin Hau", "Pauc" },
	{ "Proto-Cuneiform", "Pcun" },
	{ "Proto-Elamite", "Pelm" },
	{ "Old Permic", "Perm" },
	{ "Phags-pa", "Phag" },
	{ "Inscriptional Pahlavi", "Phli" },
	{ "Psalter Pahlavi", "Phlp" },
	{ "Book Pahlavi", "Phlv" },
	{ "Phoenician", "Phnx" },
	{ "Klingon", "Piqd" },
	{ "Miao", "Plrd" },
	{ "Inscriptional Parthian", "Prti" },
	{ "Proto-Sinaitic", "Psin" },
	{ "Ranjana", "Ranj" },
	{ "Rejang", "Rjng" },
	{ "Hanifi Rohingya", "Rohg" },
	{ "Rongorongo", "Roro" },
	{ "Runic", "Runr" },
	{ "Samaritan", "Samr" },
	{ "Sarati", "Sara" },
	{ "Old South Arabian", "Sarb" },
	{ "Saurashtra", "Saur" },
	{ "SignWriting", "Sgnw" },
	{ "Shavian", "Shaw" },
	{ "Sharada", "Shrd" },
	{ "Shuishu", "Shui" },
	{ "Siddham", "Sidd" },
	{ "Khudawadi", "Sind" },
	{ "Sinhala", "Sinh" },
	{ "Sogdian", "Sogd" },
	{ "Old Sogdian", "Sogo" },
	{ "Sora Sompeng", "Sora" },
	{ "Soyombo", "Soyo" },
	{ "Sundanese", "Sund" },
	{ "Syloti Nagri", "Sylo" },
	{ "Syriac", "Syrc" },
	{ "Tagbanwa", "Tagb" },
	{ "Takri", "Takr" },
	{ "Tai Le", "Tale" },
	{ "New Tai Lue", "Talu" },
	{ "Tamil", "Taml" },
	{ "Tangut", "Tang" },
	{ "Tai Viet", "Tavt" },
	{ "Telugu", "Telu" },
	{ "Tengwar", "Teng" },
	{ "Tifinagh", "Tfng" },
	{ "Tagalog", "Tglg" },
	{ "Thaana", "Thaa" },
	{ "Thai", "Thai" },
	{ "Tibetan", "Tibt" },
	{ "Tirhuta", "Tirh" },
	{ "Tangsa", "Tnsa" },
	{ "Toto", "Toto" },
	{ "Ugaritic", "Ugar" },
	{ "Vai", "Vaii" },
	{ "Visible Speech", "Visp" },
	{ "Vithkuqi", "Vith" },
	{ "Warang Citi", "Wara" },
	{ "Wancho", "Wcho" },
	{ "Woleai", "Wole" },
	{ "Old Persian", "Xpeo" },
	{ "Cuneiform", "Xsux" },
	{ "Yezidi", "Yezi" },
	{ "Yi", "Yiii" },
	{ "Zanabazar Square", "Zanb" },
	{ nullptr, nullptr }
};

struct _character_accent_pair {
	const char32_t character;
	const char32_t *accented_character;
};

static _character_accent_pair _character_to_accented[] = {
	{ 'A', U"Å" },
	{ 'B', U"ß" },
	{ 'C', U"Ç" },
	{ 'D', U"Ð" },
	{ 'E', U"É" },
	{ 'F', U"F́" },
	{ 'G', U"Ĝ" },
	{ 'H', U"Ĥ" },
	{ 'I', U"Ĩ" },
	{ 'J', U"Ĵ" },
	{ 'K', U"ĸ" },
	{ 'L', U"Ł" },
	{ 'M', U"Ḿ" },
	{ 'N', U"й" },
	{ 'O', U"Ö" },
	{ 'P', U"Ṕ" },
	{ 'Q', U"Q́" },
	{ 'R', U"Ř" },
	{ 'S', U"Ŝ" },
	{ 'T', U"Ŧ" },
	{ 'U', U"Ũ" },
	{ 'V', U"Ṽ" },
	{ 'W', U"Ŵ" },
	{ 'X', U"X́" },
	{ 'Y', U"Ÿ" },
	{ 'Z', U"Ž" },
	{ 'a', U"á" },
	{ 'b', U"ḅ" },
	{ 'c', U"ć" },
	{ 'd', U"d́" },
	{ 'e', U"é" },
	{ 'f', U"f́" },
	{ 'g', U"ǵ" },
	{ 'h', U"h̀" },
	{ 'i', U"í" },
	{ 'j', U"ǰ" },
	{ 'k', U"ḱ" },
	{ 'l', U"ł" },
	{ 'm', U"m̀" },
	{ 'n', U"ή" },
	{ 'o', U"ô" },
	{ 'p', U"ṕ" },
	{ 'q', U"q́" },
	{ 'r', U"ŕ" },
	{ 's', U"š" },
	{ 't', U"ŧ" },
	{ 'u', U"ü" },
	{ 'v', U"ṽ" },
	{ 'w', U"ŵ" },
	{ 'x', U"x́" },
	{ 'y', U"ý" },
	{ 'z', U"ź" },
};

#endif // LOCALES_H
