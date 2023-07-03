import { ShoplistType } from '../type/shoplist.type';

export class CreateShoplistDto {
  bruker: string;
  dropSted: number;
  komponenter: ShoplistType[];
}
